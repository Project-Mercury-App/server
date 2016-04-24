# Project Mercury Application Server
The backend server portion of Project Mercury

## Prerequisites:
 * git
 * g++
 * cmake
 * libpqxx-dev

## To Install:
```shell
$ git clone https://github.com/Project-Mercury-App/server.git
$ git submodule update --init mongoose-cpp
$ git submodule update --init pqxx
$ cd server/mongoose-cpp
$ cmake .
$ sudo make install mongoose
$ cd ../pqxx
$ ./configure
$ sudo make install
$ cd ..
$ make
```

## To Run:
1. Make sure your host is exposed to the Internet. I suggest using [ngrok](https://ngrok.com/). Install ngrok in the "server" directory and run it like so:
```shell
$ ./ngrok http 8080
```

2. Go to [Twilio's Phone Numbers management page](https://www.twilio.com/user/account/phone-numbers) and click on the phone number you want to use for this server. Then, under Configure -> Messaging -> Request URL, put your server URL (if you're using ngrok, the URL should be displayed in your terminal), and make sure the drop-down menu is on HTTP POST.
**NOTE**: If you are using ngrok, this process will need to be repeated any time you stop your ngrok process and restart it, since it assigns new addresses every time it starts. You can start and stop your server application all you want, but restarting ngrok breaks it.

3. Set your environment variables and start the server application:
```shell
$ env pghost={The Address of Your Database} pgdbname={Database Name} pguser={Database Username} pgpassword={Database Password} ./serve.o
```

## To Get Data:
Send a text message to the phone number you set up in Twilio. You should see the data your application received come through your terminal, and you'll see a nice little verification message to your phone saying you've successfully contacted the server.
**Note:** At this particular moment, the server's phone number is hard-coded into serve.cpp on line 15. So, change the variable TWILIO_NUM to the number associated with your Twilio account.
```shell
$ make
```
