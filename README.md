SynologyAPI
===========

A library to connect to the API of a Synology box. Primarily focused on the AudioStation – for now.

This is supposed to a learning project. To learn C++ and writing clean well documented code - if possible. Since it is a learning project it will probably have a ton of mistakes and illformed code in it. 

If someone has suggestions on how to improve please write an email or make a pull request. The lack of Documentation on the AudioStation API make it kinda hard to work with. I am doing everything with "reverse engineering" via Wireshark and my trusted phone and peeking over to zzarbi.

Use without any warranty.

TODO
===========
Loading covers from cover.cgi

Loading stream from stream.cgi

USAGE
===========
1)  Create object – api::AudioStationAPI("httpt", "URL", port);

2)  call api->LogIn("user", "password");

    call methods to get song, artist, album info

3)  Logout – api->LogOut();

THX
===========
Thx to zzarbi – got ideas from his work: https://github.com/zzarbi/synology/blob/master/library/Synology/