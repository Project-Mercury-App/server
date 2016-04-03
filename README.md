# Project Mercury Application Server
The backend server portion of Project Mercury

## To Install:
```shell
$ git clone https://github.com/Project-Mercury-App/server.git
$ cd server/mongoose-cpp
$ cmake .
$ make install mongoose
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

3. Start the server application:
```shell
$ ./serve.o
```

## To Get Data:
Send a text message to the phone number you set up in Twilio. You should see the data your application received come through your terminal, and you'll see a nice little verification message to your phone saying you've successfully contacted the server.
**Note:** At this particular moment, the "From" and "To" phone numbers are hardcoded in line 30 of serve.cpp. Change "From" to your Twilio number and "To" to the number you want to receive the verification text to, and recompile:
```shell
$ make
```
