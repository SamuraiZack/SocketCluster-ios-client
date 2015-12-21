//
//  SCChannel.h
//  
//
//  Created by Anatoliy Popov on 20.12.15.
//  Copyright © 2015 Anatoliy Popov. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^SCChannelSubscribeHandler)(id responce);

typedef void(^SCChannelSubscribeFailHandler)(NSError* error,id responce);


typedef enum _CHANNEL_STATE {
    
    CHANNEL_STATE_UNSUBSRIBED =0 ,
    CHANNEL_STATE_PENDING,
    CHANNEL_STATE_SUBSCRIBED
    
} CHANNEL_STATE;
@protocol SCChannelDelegate<NSObject>

-(void)SCChannel:(nonnull id/*<SCChannel>*/) channel recieveData:(nullable id)data;
-(void)SCChannel:(nonnull id/*<SCChannel>*/) channel kickOutWithMessage:(nullable id)message;

@end


@interface SCChannel : NSObject

@property (assign, nonatomic) id <SCChannelDelegate>delegate;

@property (nonatomic, copy) SCChannelSubscribeHandler SubsscribeSuccessBlock;
@property (nonatomic, copy) SCChannelSubscribeFailHandler SubscribeFailBlock;
@property NSInteger cid;
@property CHANNEL_STATE state;

-(nonnull instancetype) initWithChannelName:(nonnull NSString*)channelName andDelegate:(nullable id /*<SCChannelDelegate>*/)delegate;

-(nonnull NSString*)getName;



-(void)subscribeWithSuccess:(nullable void (^)(id responce))success withFail:(nullable void (^)(NSError* error,id responce))fail;


-(BOOL) isEqual:(nonnull SCChannel*)object;

@end
