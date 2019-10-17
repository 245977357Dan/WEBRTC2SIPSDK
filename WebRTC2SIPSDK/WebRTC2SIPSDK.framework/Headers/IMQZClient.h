//
//  IMQZClient.h
//  QzIMLib
//
//  Created by DongDong on 2019/8/16.
//  Copyright © 2019 qizhi. All rights reserved.
//

#import <Foundation/Foundation.h>
@class IMQZError;
#define CallMessageNotification @"callMessageNotification"
//呼叫状态
typedef NS_ENUM(NSInteger, CallStatus) {
    //对方呼叫我
    Start_Call = 1,
    //对方拒接
    Reject_Call = 2,
    //对方接听
    Connected_Call = 3,
    //对方挂断
    Hangup_Call = 4,
    //对方忙
    Busy_Call = 5,
    //无响应
    NoResponse_Call = 6
};

/**
 *  呼叫任务状态
 */
typedef NS_ENUM(NSInteger, CallTaskStatus)
{
    Normal_Status = 0,//默认状态
    Record_Status,//录音状态
    AudioCall_Status,//语音通话
    VideoCall_Status,//视频通话
    PhoneCall_Status//电话
};

NS_ASSUME_NONNULL_BEGIN

/*!
 IM消息接收的监听器
 
 @discussion
 收到所有的新消息都会除非该方法
 */
@protocol IMQZClientReceiveMessageDelegate <NSObject>
/**
 * @brief 监听消息
 * @param message 接收的消息
 */
- (void)onReceived:(NSDictionary *)message;

/**
 * @brief 连接状态
 * @param connectStatus 1已连接, -1未连接, -2不连接(默认值), 0连接中, 2消息收取中, -3重连超时
 */
- (void)connectStatus:(NSInteger)connectStatus;

/**
 * @brief 账号挤出 挤出之后，该设备会退出登录，断开连接。
 * @param error 挤出原因
 */
- (void)accountOut:(IMQZError*)error;
@end


@interface IMQZClient : NSObject

+ (IMQZClient *)sharedInstance;

/**
 * @brief 连接IM服务器
 * 如果登录成功，将开启重连模式，可以通过connectStatus监听连接状态。
 * 如果登录失败，发起回调，不再执行下一步。
 * 如果是网络问题，请在网络正常的情况下再次调用该方法。如果是服务器错误，请及时跟我们客服反馈。
 * @param appid 客户在启智平台申请的应用id，必传。
 * @param uuid 用户的唯一标识，必传。
 * @param complete 连接成功或者失败都会调用block。
 */
+ (void)connectIMServersWithAppid:(NSString*)appid uuid:(NSString*)uuid complete:(void (^)(IMQZError *error))complete;

//重连成功回调
@property (nonatomic, strong) void (^reconnectSuccessBlock)(void);

//用户IM系统唯一标识
@property (nonatomic, copy, readonly) NSString *userid;
//加密串
@property (nonatomic, copy, readonly) NSString *token;
//用户在启智平台申请的应用id
@property (nonatomic, copy) NSString *appid;
//用户账户 用户系统唯一标识
@property (nonatomic, copy) NSString *uuid;
//呼叫任务状态 默认为Normal_Status 可以正常接听电话，其它其情况都会被退回，提示对方用户忙
@property (nonatomic, assign, readonly) CallTaskStatus callTaskStatus;

#pragma mark 消息接收监听
/**
 * @brief 如果希望onReceived:被调用 必须设置Delegate
 */
- (void)setReceiveMessageDelegate:(id<IMQZClientReceiveMessageDelegate>)delegate;

/**
 * @brief 设置最大重连次数 超过最大重数，不再重连，SDK回调connectStatus:
 * @param count 默认值100 取值范围 <=100 >=5
 */
- (void)setMaxReconnectionLimit:(NSUInteger)count;

/**
 * @brief 发送聊天消息 公开
 * @param model 通用消息模型。
 * @param response 返回成功失败信息。
 */
- (void)sendMsg:(IMQZMessageModel*)model response:(void (^)(id responseObject))response;

//消息回执的block字典
@property (nonatomic, strong) NSMutableDictionary *msgResponseBlockMDic;
//声明消息回执的类型
typedef void (^MSGResponseBlock)(id responseObject);

/** sipCall
 * @brief 发起呼叫 关闭通话视图之前必须调用cancelCall或者disconnectedCall
 * @param complete 返回错误信息
 */
- (void)sipCall:(NSString*)callee isSip:(BOOL)isSip callType:(NSString*)callType complete:(void (^)(IMQZError *error))complete;

/**
 * @brief 取消呼叫
 * @param complete 返回错误信息
 */
- (void)cancelCall:(void (^)(IMQZError *error))complete;

/**
 * @brief 接通来电
 * @param complete 返回错误信息
 */
- (void)connectedCall:(void (^)(IMQZError *error))complete;

/**
 * @brief 拒绝接听
 * @param complete 返回错误信息
 */
- (void)rejectedCall:(void (^)(IMQZError *error))complete;

/**
 * @brief 挂断电话
 * @param complete 返回错误信息
 */
- (void)disconnectedCall:(void (^)(IMQZError *error))complete;

/**
 * @brief 设置免提
 * @param enableSpeaker YES:开启 NO:关闭
 * @return 0:成功  <0:失败
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 * @brief 设置静音
 * @param mute YES:开启 NO:关闭
 * @return 0:成功  <0:失败
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 * @brief 开始录音
 * @param path 保存路径
 * @param quality 录音质量 0:低 1:中 2:高
 * @return 0:成功  <0:失败
 */
- (int)startAudioRecording:(NSString*)path quality:(NSUInteger)quality;

/**
 * @brief 获取我的小号
 */
- (void)getBindPhone;
@end

NS_ASSUME_NONNULL_END
