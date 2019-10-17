//
//  IMQZDataManager.h
//  WebRTC2SIPSDK
//
//  Created by DongDong on 2019/9/9.
//  Copyright © 2019 qizhi. All rights reserved.
//

#import <Foundation/Foundation.h>
@class IMQZMessageModel;
@class FMDatabaseQueue;

NS_ASSUME_NONNULL_BEGIN

@interface IMQZDataManager : NSObject
+ (IMQZDataManager*)shareManager;
//固定格式 yyyy-MM-dd HH:mm:ss
@property (nonatomic, strong) NSDateFormatter *formatter;
//固定格式 yyyy-MM-dd HH:mm
@property (nonatomic, strong) NSDateFormatter *formatter_ss;
//消息数据库队列
@property (nonatomic, strong) FMDatabaseQueue *dataQueue;

/**
 * @brief 通讯模块 插入会话模型消息
 * @param model 消息模型
 */
+ (void)insertMessage:(IMQZMessageModel*)model;

/**
 * @brief 获取会话列表数据 无序
 * @param complete 返回IMQZMessageModel消息数组
 */
+ (void)getSessionList:(void(^)(NSMutableArray *modelList))complete;

/**
 * @brief 获取聊天历史消息
 * @param targetid 目标id 单聊:对方的userid 群聊:群id
 * @param index 消息索引 默认从1开始
 * @param page 获取的消息数量
 * @param complete 返回IMQZMessageModel消息数组
 */
+ (void)getChatMessageListWithTargetId:(NSString*)targetid index:(NSUInteger)index page:(NSUInteger)page complete:(void(^)(NSMutableArray *modelList))complete;

/**
 * @brief 更新消息状态
 * @param status -1:发送失败 0:发送中 1:发送成功 2:对方已读（暂不支持）
 */
+ (void)updateMessageStatus:(NSString*)status;

/**
 * @brief 消息置顶
 * @param targetid 单聊:对方userid 群聊:群组id
 */
+ (void)setTopWithTargetid:(NSString*)targetid;

/**
 * @brief 获取SDK版本号
 */
+ (NSString*)getVersions;
@end

NS_ASSUME_NONNULL_END
