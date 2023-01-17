
# Peer To Peer Chat

Peer To Peer Chat is the chatroom where users can communicate with no centralized server.
Written in C and uses UDP packets.



## Functionality:
- When connecting to one user, the rest are connected automatically
- Disconects user if he do not answer with ping packets for a long time
- Ability to use nicknames
- Ability to choose user port
## Screenshots

![App Screenshot](https://github.com/real-mozzevelnik/PeerToPeerChat/blob/main/screenshot.png?raw=true)


## Dependencies
- [ncurses](https://invisible-island.net/ncurses/announce.html) - C language UI library
## Installation

Install project using:

```bash
  git clone --depth=1 https://github.com/real-mozzevelnik/PeerToPeerChat PeerToPeerChat
  cd PeerToPeerChat
```
    
## Deployment

To deploy this project run:

```bash
  make app
```

