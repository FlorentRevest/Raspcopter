Repository description
==========

This git repo contains three directories,  all of them are related to the same project: A home-made quadcopter running a Raspberry Pi.

 * raspberrypi-server: This software, made in C++ is a flight controller intended to be run on the R-Pi, it basically do three things:
    - it collects the values from the accelerometer and gyroscope via i2c (magnetometer and barometer may be added later) 
    - it filters these values via the DMP of the accelerometer
    - it manages the motors speed via the Pololu Maestro board according to the above values
    - it communicates over wifi with one of the two clients below
 * android-client: The Android smartphone is a wifi hotspot with whom the R-Pi communicates. An app (in java) will also be made to provide a handy controller.
 * laptop-client: This client, written in C++ with Qt is intended to be a complete "ground station" with recorded logs and real-time informations on the quadcopter. The laptop will also connect to the Android smartphone to be on the same local network as the raspberry pi.

## Used pieces
 * 4 Motors: [FC 28-22 Brushless Outrunner 1200kv](vhttp://www.hobbyking.com/hobbyking/store/uh_viewitem.asp?idproduct=5354)
 * 4 ESC(Electronic Speed Controllers): [Hobby King 20A ESC 3A UBEC](http://www.hobbyking.com/hobbyking/store/__15202__hobby_king_20a_esc_3a_ubec.html)
 * 1 Propellers pack (two of each directions): [Slow Fly Electric Prop 1045SF (4 pc)]( http://www.hobbyking.com/hobbyking/store/__22446__Slow_Fly_Electric_Prop_1045SF_4_pc_.html) 
 * 1 Frame: [Hobbyking X525 V3 Glass Fiber Quadcopter Frame 600mm](http://www.hobbyking.com/hobbyking/store/__22800__hobbyking_x525_v3_glass_fiber_quadcopter_frame_600mm.html)
 * 1 Battery: [Turnigy 2200mAh 3S 20C Lipo Pack](http://www.hobbyking.com/hobbyking/store/__8932__Turnigy_2200mAh_3S_20C_Lipo_Pack.html)
 * 1 Battery charger: [Turnigy 2S 3S Balance Charger. Direct 110/240v Input](http://www.hobbyking.com/hobbyking/store/uh_viewitem.asp?idproduct=8247)
 
(the pieces above have been commanded at the same time from HobbyKing despite their non-professionalism... I waited this pack a month and a half)

 * An ESC/servos USB communication board:  [Micro Maestro 6-Channel USB Servo Controller](http://www.pololu.com/catalog/product/1350)
 * A low battery alarm: [Lipo Battery alarm](http://www.ebay.fr/itm/2S-4S-7-4V-14-8V-RC-Lipo-Batterie-Tension-Faible-Testeur-Buzzer-Alarme-autonomie-/130732900168?pt=FR_YO_Jeux_RadioComRobots_VehiculesRadiocommandes&hash=item1e7049bf48)
 * Accelerometer and gyroscope: [MPU6050 board](http://www.ebay.fr/itm/MPU-6050-Module-3-Axis-Gyroscope-Accelerometer-Sensor-for-Arduino-DIY-/400487483979?pt=AU_B_I_Electrical_Test_Equipment&hash=item5d3eea0a4b#ht_3042wt_1166)
 * Connections: [Some cables used in the SimonK flashing process and in the MPU6050 communication](http://www.ebay.fr/itm/40-Cables-pour-BreadBoard-Femelle-Femele-Arduino-Femalle-Fils-jumper-Wire-/330902593748?pt=FR_YO_MaisonJardin_Bricolage_ElectroniqueComposants&hash=item4d0b54e0d4#ht_2467wt_1406)
 * Screws of a lot of size
 * 4 Propellers Adapters from GForce in a local store
