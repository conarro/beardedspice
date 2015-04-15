//
//  AppDelegate.h
//  BeardedSpice
//
//  Created by Tyler Rhodes on 12/8/13.
//  Copyright (c) 2013 Tyler Rhodes / Jose Falcon. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "SPMediaKeyTap.h"

#import "Chrome.h"
#import "Safari.h"
#import "iTunes.h"
#import "TabAdapter.h"
#import "MediaStrategyRegistry.h"

@class runningSBApplication;

extern BOOL accessibilityApiEnabled;

@interface BeardedSpiceApp : NSApplication
@end

#import "MediaStrategy.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSUserNotificationCenterDelegate> {
    IBOutlet NSMenu *statusMenu;
    NSUInteger  statusMenuCount;
    NSStatusItem *statusItem;

    runningSBApplication *chromeApp;
    runningSBApplication *canaryApp;
    runningSBApplication *yandexBrowserApp;

    runningSBApplication *safariApp;
    
    runningSBApplication *iTunesApp;
    BOOL iTunesNeedDisplayNotification;

    SPMediaKeyTap *keyTap;

    TabAdapter *activeTab;
    NSString *activeTabKey;
    
    NSMutableArray *playingTabs;
    
    MediaStrategyRegistry *mediaStrategyRegistry;

    NSWindowController *_preferencesWindowController;
    
    NSMutableSet    *openedWindows;
}

@property (nonatomic, readonly) NSWindowController *preferencesWindowController;

- (IBAction)openPreferences:(id)sender;
- (void)showNotification;

@end
