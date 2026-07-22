
# Process for flashing arduino with RP via ssh

```
mkdir -p ~/local/bin
```

#### install arduino-cli
run from ~/$

```
curl -fsSL "https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh" | BINDIR=~/local/bin sh
```
path global command
```
echo "PATH=\"\$PATH:\$HOME/local/bin\"" >> $HOME/.bashrc  
```
```
source $HOME/.bashrc
```
init arduino

```
arduino-cli config init	
```
update available boards, libraries
```
arduino-cli core update-index
```
```
arduino-cli board list 	## what arduino plugin and core
```
#### if fqbn blank:

```
arduino-cli core install arduino:avr  	## find right board, avr example
```
mycode is your sketch
```
arduino-cli sketch new mycode 
```
```
cd mycode
```
~/mycode$   
```
nano MySketch.ino
```
#### complile:
```
arduino-cli compile --fqbn arduino:avr:nano temp_relay.ino
```
#### upload: 
``` 
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano MySketch.ino
```
#### print serial monitor in terminal
~/mycode$
```
arduino-cli monitor -p /dev/ttyUSB0 --config baudrate=9600
```