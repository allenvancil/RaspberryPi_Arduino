
# Process for flashing arduino with RP via ssh

#### install arduino-cli
run from ~/$

```
curl -fsSL "https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh" | BINDIR=~/local/bin sh

~>> echo "PATH=\"\$PATH:\$HOME/local/bin\"" >> $HOME/.bashrc  ##path global command
~>> source $HOME/.bashrc
~>> arduino-cli config init	## init arduino

~>> arduino-cli core update-index		## update available boards, libraries

~>> arduino-cli board list 	## what arduino plugin and core
```
#### if fqbn blank:

```
~>> arduino-cli core install arduino:avr  	## find right board, avr example

~>> arduino-cli sketch new mycode  ## input code into
>> cd mycode
~/mycode>> nano MySketch.ino

```
#### complile:
```
~/mycode>> arduino-cli compile --fqbn arduino:avr:nano temp_relay.ino
```
#### upload: 
``` 
~/mycode>> arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano temp_relay.ino
```
#### print serial monitor in terminal
```
~/temp_relay>> arduino-cli monitor -p /dev/ttyUSB0 --config baudrate=9600
```