# PC-HiFi
PC HiFi


1,What is PC HiFi ?

	In normal sound worker , We use three speakers to playback 
	high , middle ,low frequency audio , how we separate sound 
	signal ? we use permittance and pole brace .

	Now we have differant way to separate sound signal , use a 
	PC , to get wave file data by a computer program , and then 
	proccess science calculation to separate sound signal , and 
	send to three sound cards to playback audio, if you can 
	install three sound cards on your PC , you can playback audio 
	file correctly.

2,Why use PC HiFi play audio file ?

	When audio pass a permittance ,	there are 180 degrees phase 
	change , when audio pass a pole brace , there are 180 degrees 
	phase change in another direction , if you want listening 
	better sound , you should don't that it happen .

3,What is best ?

	Now , a PC can only install three sound cards , if you can 
	install 9 sound cards , we can separate audio to 9 chanel ,
	if that ,a speaker can only playback 100Hz-->200Hz or 
	1k-->2kHz audio , this will makes low fuzzy of playback , 
	you can playback some frequency audio by most suitable speaker .

4,How to install three sound card ?

	To let program to recognize three sound cards , you need three 
	differant brand sound cards , usually there is a AC'97 sound 
	card in motherboard , you can buy a C-Media 8738 sound card 
	and a CREATIVE BLASTER 5.1 sound card (for example),
	
	To install 3 sound cards , better one by one , if you install 
	3 sound cards in same time , there may be a lot of errors .

	after you installed AC'97 sound card , you can click 
	'My Computer'->'Propertiy'->'Hardware'->'Device Manager' ,
	to disable some devices on sound card that you don't need ,
	to disable 'MIDI Device' and 'Standerd Game Port' , only left
	a wave playback device , this is for reduce resource requirement , 
	so you can install more sound cards .

	next install C-Media 8738 sound card , and also disable 
	'MIDI Device' and 'Standerd Game Port' , only left a wave 
	playback device .

	at last install CREATIVE BLASTER 5.1 sound card , and also 
	disable 'MIDI Device' and 'Standerd Game Port' , only left a 
	wave playback device .

	you don't need disable other devices that are not in a sound card .

5,Install AMP and sound worker

	You need three same AMP , and a sound worker with high,middle,low 
	frequency speakers. AMP directly connect to speaker , you don't
	need crossovers .

	at first time ,you don't know which sound card is low frequency 
	channel ,if high volume low frequency audio been send to high 
	frequency speaker , maybe damage it . so you can connect low 
	frequency speaker to AMP first , and connect this AMP to one sound 
	card , listen a while , if this channel isn't low frequency ,
	you can change to another sound card .
        
	at second step , connect middle frequency speaker in same way ,
	at last connect high frequency speaker .

6,Adjust left and right channel 

	After this system been installed , in some times , left and right 
	channel are not correctly connected . one or two left channel maybe
	been connected as right channel . you can run this program , click
	a button called 'Test left' , it will play a WAV file and only play
	left channel (this WAV file must already been transformed) .  if 
	you find a channel isn't correctly connected , you can adjust it .

7,Reduce transform fuzzy 

	After transform of a WAV file is finished , program will display a
	fuzzy rate , this rate usually is 1-2/10000 , if this rate is very 
	high , for example 1-2/1000 or 1-2/100 , you can start Windows
	Application 'Recorder' , open this WAV file , select menu 'Reduce Volume'
	three times and save , and then will make low transform fuzzy rate .
	it is because if WAV file's volume is too high , may cause overflow 
	when program proccessing calculation , so need to reduce volume .

8,Play music 

	Now you can play music , set three AMP's volume at best position ,
	run this program ,click button 'Syn Play' . when you play music ,
	better don't run other program .

9,PC Platform :

	PC with Windows 2000/XP/VISTA , CPU 1Ghz or more ,memory 256MB or 
	more , 3 soundcards installed .

10,Software guide :

	(1) Use software tools (for example :CDCOPY) copy CD to WAV file on harddisk .
	(2) Start pc_hifi_trans.exe , Select the name of WAV , Click "prepare all",
	    that will make three chanel files .
	(3) Start pc_hifi_player.exe, Select WAV file name ,Click "syn play",
	    That will playback music in three sound cards in same time .


















