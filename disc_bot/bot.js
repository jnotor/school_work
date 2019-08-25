/* resources:
https://www.digitaltrends.com/gaming/how-to-make-a-discord-bot/
https://www.devdungeon.com/content/javascript-discord-bot-tutorial
https://stackoverflow.com/questions/50710598/using-discord-js-to-detect-image-and-respond
https://github.com/DV8FromTheWorld/JDA/blob/master/src/examples/java/MessageListenerExample.java
*/
var Discord = require('discord.io');
var logger = require('winston');
var auth = require('./auth.json');

// Configure logger settings
logger.remove(logger.transports.Console);
logger.add(new logger.transports.Console, {
    colorize: true
});
logger.level = 'debug';
// Initialize Discord Bot
var bot = new Discord.Client({
   token: auth.token,
   autorun: true
});
bot.on('ready', function (evt) {
    logger.info('Connected');
    logger.info('Logged in as: ');
    logger.info(bot.username + ' - (' + bot.id + ')');
});
bot.on('message', function (user, userID, channelID, message, evt) {
    if (channelID == 614949965021708329){
        if (userID == 155564652208717824) {
            if (message.substring(0,1) == '') {
                    bot.sendMessage({
                            to: channelID,
                            message: 'Nice meme, Daniel!'
                    });
                }
            }
        if (message.substring(0,1) == '!') {
            bot.sendMessage({
                to: channelID,
                message: 'Hey' //+ message.author.toString()
            });
        }
        }
    });
bot.on('message', (receivedMessage) => {
    // Prevent bot from responding to its own messages
    if (receivedMessage.author == bot.user) {
        return
    }

    receivedMessage.channel.send("Message received from " + receivedMessage.author.toString() + ": " + receivedMessage.content)
})