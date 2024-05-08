


  // **********************************************************
  void CRSF_Receive() 
  {
  #if (PROTOCOL == 9)   //  CRSF Serial
    if (crsf.readCrsfFrame(crsf.frame_lth))  // got a frame
    {
      uint8_t crsf_id = crsf.decodeTelemetry(&*crsf.crsf_buf);
      if (crsf_id == GPS_ID)   // 0x02
      {
        // don't use gps heading, use attitude yaw below
        cur.lon = crsf.gpsF_lon;
        cur.lat = crsf.gpsF_lat;    
        cur.alt = crsf.gps_altitude;
          
        gpsfixGood = (crsf.gps_sats >=5);  
        lonGood = (crsf.gps_lon != 0);
        latGood = (crsf.gps_lat != 0);
        altGood = (crsf.gps_altitude != 0);
        hdgGood = 1;
        cur.alt_ag = cur.alt - hom.alt;
        hud_num_sats = crsf.gps_sats;         // these for the display
        hud_grd_spd = crsf.gpsF_groundspeed;
       // hud_rssi
        //motArmed
       // pt_home_dist
       // hud_climb 
  #if defined DEBUG_CRSF_GPS          
        log.print("CRSF_GPS:");
        crsf.printByte(crsf_id, ' ');
        log.printf("lat:%2.7f  lon:%2.7f", crsf.gpsF_lat, crsf.gpsF_lon);
        log.printf("  ground_spd:%.1fkm/hr", crsf.gpsF_groundspeed);
        log.printf("  hdg:%.2fdeg", crsf.gpsF_heading);
        log.printf("  alt:%dm", crsf.gps_altitude);
        log.printf("  sats:%d\n", crsf.gps_sats); 
  #endif          
      }
      if (crsf_id == BATTERY_ID) 
      { 
        hud_bat1_volts = crsf.batF_voltage;           
        hud_bat1_amps = crsf.batF_current;
        hud_bat1_mAh = crsf.batF_fuel_drawn * 1000;
  #if defined DEBUG_CRSF_BAT        
        log.print("BATTERY id:");
        crsf.printByte(crsf_id, ' ');
        log.printf("volts:%2.1f", crsf.batF_voltage);
        log.printf("  amps:%3.1f", crsf.batF_current);
        log.printf("  Ah_drawn:%3.1f", crsf.batF_fuel_drawn);
        log.printf("  remaining:%3u%%\n", crsf.bat_remaining);
  #endif 
      }
     
      if (crsf_id == ATTITUDE_ID)
      {
        cur.hdg = crsf.attiF_yaw;
  #if defined DEBUG_CRSF_ATTI
        log.print("ATTITUDE id:");
        crsf.printByte(crsf_id, ' '); 
        log.printf("pitch:%3.1fdeg", crsf.attiF_pitch);
        log.printf("  roll:%3.1fdeg", crsf.attiF_roll);
        log.printf("  yaw:%3.1fdeg\n", crsf.attiF_yaw);  
  #endif          
      }    
  
      if (crsf_id == FLIGHT_MODE_ID)
      {
  #if defined DEBUG_CRSF_FLIGHT_MODE 
        log.print("FLIGHT_MODE id:");
        crsf.printByte(crsf_id, ' ');
        log.printf("lth:%u %s\n", crsf.flight_mode_lth, &crsf.flightMode);
  #endif
      gpsGood = hbGood = gpsfixGood & lonGood & latGood & altGood;    
      if (gpsGood) gpsGood_millis = millis();     // Time of last good GPS packet 
      hbGood_millis= millis();                    // good GPS data is equivalent to a mavlink heartbeat
      }
    }      
    
    #if defined DEBUG_GOODFLAGS
      log.printf("gpsGood:%u  gpsfixGood:%u  lonGood:%u  latGood:%u  altGood:%u  hdgGood:%u  boxhdgGood:%u \n", gpsGood, gpsfixGood, lonGood, latGood, altGood, hdgGood, boxhdgGood);           
    #endif
#endif // end of CRSF Serial    
  }    

        
