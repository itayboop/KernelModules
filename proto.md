-----------------------------------------
The great leader of the netlink protocol
------------------------------------------------
|  Magic  | Packet type | Packet lenght | Data |
|0x13|0x37|  ----TT---- | ---- LL ----- | .... |
------------------------------------------------

Packet types:
 - 0x0: start
	- start the module functunality

 - 0x1: stop
	- stop it babe, its trivial

 - 0x2: register
	- register the module to the manager

 - 0x3: unregister
	- unregister it my friend

example: 0x13,0x37,0x0,0x0 -- basic start packet
