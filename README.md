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



在普通的高保真音箱中

   
    我们用三个扬声器,播放 高,中,低频率的声音,我们用电容和电感分解声音信号.
    现在我们可以用更好的办法去分解声音信号,用一个PC机,用计算机程序获得CD文件
    数据,然后用PC机进行科学计算,分解声音信号为高频,中频,低频三个声道,送给三
    个声卡播放声音。

为什么?

   当声音信号通过一个电容,有180度的相位变化,当声音信号通过一个电感,有180度的
   另一方向的相位变化,现在的分频器又有电容，又有电感，扬声器本身也有电感，相
   位变化极大，如果你想听到高保真的声音,应该避免这种情况。

   现在,一个PC只能安装三块声卡,如果你能安装9块声卡,我们可以把声音信号分解为
   9个声道,如果那样,一个扬声器只播放100Hz-->200Hz或1k-->2kHz频率的声音,这将
   使重放的失真减小,PC分频可以无限分,用户可以用最合适的扬声器播放某个频率的
   音乐。

音响电路中

    有的电容用于稳压，是电路供电用的，不影响信号相位，有的电容用来传递信号，
    相对电阻极小，用来区分交流和直流，对信号相位的影响可以忽略，只有分频的电
    容和电感才影响相位。

如何安装三块声卡

    为了程序能够识别不同的声卡，必须安装三块不同牌子的声卡，通常有一个集成在
    主板的AC'97声卡，再购买C-Media 8738,    CREATIVE BLASTER 5.1各一块，市场
    价300元以内（2006年初）。（其它牌子型号也可以，上面提到的是实际安装成功的）

    安装时要一块一块地装，同时安装三块声卡发生故障的可能大大增加。

    安装AC'97声卡，安装完毕后，在 系统属性－》硬件－》设备管理器 中把不需要的
    声卡上的设备禁用，比如MIDI设备和“标准游戏端口”，只留一个音频播放设备，
    把资源尽量省出来，给后来安装的声卡使用。

    插入C-Media 8738声卡，安装C-Media 8738声卡，安装好后同样把MIDI设备和“标
    准游戏端口”以及其他不需要的声卡设备禁用，只留一个音频播放设备。

    插入CREATIVE BLASTER 5.1声卡，安装CREATIVE BLASTER 5.1。

    最后查看设备管理器，看到三个安装正常的声卡就可以了。其它不是声卡的设备没
    有影响，不需要因此禁用某些设备。

    由于声卡不同，音量有很大差别，在 控制面板－》音频设备 中，先把一块声卡设
    为首选设备，调整音量，然后再用同样的方法设置其他声卡，直到三个声卡音量基
    本相同为止。

安装功放音箱

    这时就可以使用播放软件，开始时可以接入三对全频无源音箱（每个价格估计在10
    几元），直接插在声卡的输出上。

    最好是有三个一样的HiFi功放，AV功放更常见，价格也便宜，通常有Direct模式，
    也可以考虑购买（AV功放价格约为600－700元每个）。还要一对配有高音，中音，
    低音扬声器的音箱，三个功放分别接高中低三对扬声器（直接接喇叭，不要分频器）
    （自己组装一对音箱约需500元）。

    因为哪个声道是低音还不确定，万一大功率低音接入高频扬声器会损坏扬声器，
    所以先接通低音扬声器，再选择声卡输出，根据发出的声音确定输出低音的声卡。
    确定好低音是哪个声卡后，再接入中音扬声器，根据发出的声音确定输出中音的声
    卡。最后接入高频扬声器。

调节左右声道位置

    整套系统安装完毕后，常常左右声道颠倒，在播放软件中，有一个“Test Left”按
    钮，可以播放已经转换好的WAV文件，而且只播放左声道，利用这个功能可以检查声
    道左右是否正确，如果有误就相应调整。

降低转换失真

    使用本软件的转换软件时，最后显示一个失真率，通常为万分之1－2左右，如果这
    个数值比较高，达到千分之几百分之几，可以这样解决，启动Windows系统的“录
    音机”，打开将要转换的WAV文件，选择“降低音量”菜单三次，然后保存。再次
    转换后就有很低的失真率。原因是原始WAV文件中，音量大的地方经过科学计算后
    容易溢出，造成失真率高，降低音量后就可以消除科学计算时的溢出。

用播放器播放音频

    最后用播放器播放音频，音频播放过程中最好不要运行其他程序，把三个声道的音
    量调节在最合适的位置，关机时先关闭功放电源。

计算机要求

    CPU主频1Ghz或以上，内存256MB或以上，操作系统为 Windows XP 或 Windows 2000 。

软件使用说明:

    (1) 用工具软件(如 CD Copy )将音乐CD复制到硬盘上,格式为*.WAV.
    (2) 启动PC_HiFi_Trans.exe,选择所复制的WAV文件,点击"Prepare All",将生成三个声
    道的文件.
    (3) 启动PC_HiFi_Player.exe,选择所复制的WAV文件,点击"Syn Play",将在三个声卡同
    时播放高,中,低频音乐.














