# Pub-Sub

Pub-Sub is a publish-subscribe system based on [socketx](https://github.com/fancyqlx/socketx). The system consists of PubSubSys, SubscriberClient and PublisherClient. The communication between them is by message passing. We give a brief introduction as follows.

## PubSubSys
PubSubSys is an agent between publisher and subscriber. It consists of PublisherStub, SubscriberStub and filter. Filter is used to dispatch messages to PublisherStub and SubscriberStub correctly. PublisherStub gets the message and analyzes it to determine what should we do next. There are two things for PublisherStub: `pub` means publisher a message with a certain theme and `unpub` is for unregist a theme. SubscriberStub has a similar function, the difference is that it handles commands `sub` and `unsub`. 

The messages with a certain theme are stored in a Message Queue, where one theme corresponds to one Queue. The message queues are responsible for listening whether there is a subscriber `sub` these theme. It sends the first message of the queue to all of the subscriber who `sub` the theme, and it guarantees that the message is only sent by once.

## SubscriberClient
SubscriberClient invokes class Subscriber for performing functions subscrib, unsubscrib and regist. It receives messages and delivers to Subscriber for a further handling. The communication between PubSubSys is just like a `RPC` process.

## PublisherClient
Like SubscriberClient, it also contains a class Publisher for performing publish and unpublish functions.