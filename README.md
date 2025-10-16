# RaspberryPi_Arduino
Raspberry pi and Arduino code and process


Setup data logging w/ DHT22 temp/humid sensors-----------------

** start by being sure the sketch works in the standard Ardiuno IDE

1. install ArduinoCLI to access Arduino IDE from command line
	a. try >> winget install Arduino.CLI
	b. if not work go directly to arduino website  --> https://arduino.github.io/arduino-cli/latest/installation/
		--> Download --> Window exe 64bit (depend of your machine)
	c. unzip file in C/program files/
	d. add to path -- >> win + R --> <sysdm.cpl> --> Advance --> Environment Variables --> Path --> Edit --> New --> add c/program files/arduinoCLI
	e. BE SURE TO CLOSE AND REOPEN TERMINAL FOR PATH TO INITIATE!!!!
	f. verify >> arduino-cli version

2.  get port, board, and fqbn  
		>> arduino-cli board list
3.  init Arduino cli	
	a. 	>> arduino-cli config init
		>> arduino-cli update-index
		>> arduino-cli install arduino:avr

	b. 	>> arduino-cli compile --fqbn arduino:avr:mega path/to/sketch.ino
		>> arduino-cli upload -p COM4 --fqbn arduino:avr:mega path/to sketch.ino
	BE SURE ALL OTHER IDE AND PROGRAMS RELATED TO ARDUINO OR COM4 CLOSED!!!!
	c. if get avrdude: stk500_getsync() attempt 1 of 10: not in sync: resp=0x00 error, close everything and reopen
		when working will say  << New upload port: COM4(serial) >>

4. 	run data output 
		>> arduino-cli monitor -p COM4 -c baudrate=9600
		should show data out as on the serial monitor in the Arduino IDE


