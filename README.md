# BeardedSpice

BeardedSpice is a menubar application for Mac OSX that allows you to control web based media players with the media keys found on Mac keyboards. It is an extensible application that works with Chrome and Safari, and can control any tab with an applicable media player. BeardedSpice currently supports:

- YouTube
- HypeMachine
- Spotify (Web)
- Pandora
- BandCamp
- GrooveShark
- SoundCloud
- Last.fm
- Google Music
- Rdio

If you want another supported app supported, simply open an issue with the tag 'app support'. Or, if you are feeling extra feisty, implement the handler yourself!

BeardedSpice is built with [SPMediaKeyTap](https://github.com/nevyn/SPMediaKeyTap) and works well with other applications listening to media key events.


[![BeardedSpice](http://imgur.com/zoeg3NS.png)](http://imgur.com/zoeg3NS.png)

## Downloading

Download the current release here *TODO*.

## Features

## Writing a Handler

Media controllers are written as strategies. Each strategy defines a collection of Javascript functions to be excecuted on particular webpages.

```Objective-C
@interface MediaStrategy : NSObject

-(BOOL) accepts:(id <Tab>) tab;
-(NSString *) displayName;

-(NSString *) toggle;
-(NSString *) previous;
-(NSString *) next;
-(NSString *) pause;

@end
```

The `accepts` method takes a `Tab` object and returns `YES` if the strategy can control the given tab. `displayName` must return a unique string describing the controller and will be used as the name shown in the Preferences panel. All other functions return a Javascript function for the particular action. `pause` is a special case and is used when changing the active tab.

A sample strategy for GrooveShark:

```Objective-C
@implementation GrooveSharkStrategy

-(id) init
{
    self = [super init];
    if (self) {
        predicate = [NSPredicate predicateWithFormat:@"SELF LIKE[c] '*grooveshark.com*'"];
    }
    return self;
}

-(BOOL) accepts:(id <Tab>)tab
{
    return [predicate evaluateWithObject:[tab URL]];
}

-(NSString *) toggle
{
    return @"(function(){return window.Grooveshark.toggle()})()";
}

-(NSString *) previous
{
    return @"(function(){return window.Grooveshark.previous()})()";
}

-(NSString *) next
{
    return @"(function(){return window.Grooveshark.next()})()";
}

-(NSString *) pause
{
    return @"(function(){return window.Grooveshark.pause()})()";
}

-(NSString *) displayName
{
    return @"Grooveshark";
}

@end
```

Update the `MediaStrategyRegistry` to include an instance of your new strategy:

```Objective-C
+(NSArray *) getDefaultMediaStrategies
{
        DefaultMediaStrategies = [NSArray arrayWithObjects:
                                  // ...
                                  [[GoogleMusicStrategy alloc] init],
                                  [[RdioStrategy alloc] init],
                                  // add your new strategy!
                                  [[GrooveSharkStrategy alloc] init],
                                  nil];
}
```

Finally, update the default preferences plist to include your strategy.

