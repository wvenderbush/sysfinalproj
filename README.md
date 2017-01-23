# CChat
By Winston Venderbush, Max Bertfield, and Jack Schluger

<hr>

### What is CChat?
CChat is a comprehensive chatroom program written in C. Users can host a server with the inclued server files and set up chatrooms that can be joined by clients on local or networked connections. Users can then seamlessly interact with other users in the chatroom, making use of our custom <b>CChat Markup Language</b> to spice-up their messages!

<hr>

### How to use it?
<b>Note</b>: <i>CChat has no dependencies! It is written entirely in native C, which makes it easy to use and quick to set up!</i>

1. Simply compile the program by typing a quick command: `$ make`
2. Once the files are compiled, start a server using `$ ./server`
3. Open a client by typing: `$ ./client`
4. Once the server is running, a client can connect to it after choosing a username by typing in that server's local or network IP address (if port forwarding is enabled)

<hr>

### CChat Markup Language (CML)

CChat comes with its own custom markup language for adding flare to your messages! You can use the markup language in any message or even when creating your username!

####Emojis
CML has a collection of emojis that you can access in chatrooms by using these commands:
CML Emoji tags begin and end with `~~`

`~~smile~~` -- Inserts the `ʘ‿ʘ` emoji
`~~shrug~~` -- Inserts the `¯\_(ツ)_/¯` emoji
`~~scared~~` -- Inserts the `⊙﹏⊙` emoji
`~~disapprove~~` -- Inserts the `ಠ_ಠ` emoji
`~~cute~~` -- Inserts the `(｡◕‿◕｡)` emoji
`~~excited~~` -- Inserts the `ヽ(*▽*)/` emoji
`~~devious~~` -- Inserts the `ಠ‿ಠ` emoji
`~~tableflip~~` -- Inserts the `(╯°□°）╯︵ ┻━┻` emoji
`~~cat~~` -- Inserts the `^ᵒᴥᵒ^` emoji
`~~fight~~` -- Inserts the `ლ(｀ー´ლ)` emoji
`~~bear~~` -- Inserts the `ʕ•ᴥ•ʔ` emoji
`~~blob~~` -- Inserts the `༼ つ ◕_◕ ༽つ` emoji
`~~cry~~` -- Inserts the `ಥ_ಥ` emoji
`~~love~~` -- Inserts the `(づ￣ ³￣)づ` emoji
`~~confused~~` -- Inserts the `(⊙_☉)` emoji
`~~fightme~~` -- Inserts the `(ง •̀_•́)ง` emoji
`~~hiding~~` -- Inserts the `|_・)` emoji
`~~sleep~~` -- Inserts the `(ᴗ˳ᴗ)` emoji

####Colors
With CML, you can also change the color of text in the chatroom by using these tags:
CML Color tags begin and end with `::`

`::red::` -- Sets the following text to red
`::black::` -- Sets the following text to black
`::white::` -- Sets the following text to white
`::green::` -- Sets the following text to green
`::yellow::` -- Sets the following text to yellow
`::blue::` -- Sets the following text to blue
`::magenta::` -- Sets the following text to magenta
`::cyan::` -- Sets the following text to cyan
`::basic::` -- Sets the following text back to the default terminal color scheme

<hr>

We hope you enjoy using CChat!






