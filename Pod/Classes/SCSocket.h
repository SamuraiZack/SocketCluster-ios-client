//
//  SCSocket.h
// 
//
//  Created by Anatoliy Popov on 03.12.15.
//  Copyright © 2015 Anatoliy Popov. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum _SOCKET_STATE {
    
    SOCKET_STATE_CONNECTING =0 ,
    SOCKET_STATE_OPEN,
    SOCKET_STATE_CLOSED
    
} SOCKET_STATE;

@class SCChannel;
@class SCMessage;

@protocol SocketClusterDelegate<NSObject>

@optional

-(void)socketClusterAuthenticateEvent:( NSString* _Nonnull)token;
-(void)socketClusterConnectEvent;
-(void)socketClusterReceivedEvent:(NSString * _Nonnull)eventName WithData:( NSDictionary *_Nullable)data isStandartEvent:(BOOL)isStandartEvent;


@end


@interface SCSocket : NSObject

@property (assign, nonatomic,nullable) id <SocketClusterDelegate>delegate;
@property (nonatomic, readonly,nonnull) NSString* socketId;



+(instancetype _Nullable)client;

- (void)initWithHost:(NSString *_Nonnull)host onPort:(NSInteger)port securely:(BOOL)isSecureConnection;

- (SOCKET_STATE)getState;
- (void)connect;
- (void)disconnect;


-(void)loginWithData:(nullable NSDictionary*)data withSuccess:(nullable void (^)(_Nullable id response))success withFail:(nullable void (^)(_Nullable id response))fail;

-(void)subscribeToChannel:(SCChannel* _Nonnull)channel;
-(void)unSubscribeFromChannel:(SCChannel* _Nonnull)channel;

-(NSInteger)sendMessage:(SCMessage* _Nonnull)message toChannel:( SCChannel* _Nullable)channel;

-(void)setRestoreChannels:(BOOL)restore;

-(NSInteger) emitEvent:(NSString* _Nonnull)event withData:(_Nullable id)data;

-(void)setMinSCReconnectTime:(NSInteger)minReconnectTime;
-(void)setMaxSCReconnectTime:(NSInteger)maxReconnectTime;

-(NSArray* _Nonnull)getSubscribedChannels;

@end
