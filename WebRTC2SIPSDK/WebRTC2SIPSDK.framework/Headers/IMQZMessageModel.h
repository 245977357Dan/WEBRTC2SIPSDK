//
//  IMQZMessageModel.h
//  WebRTC2SIPSDK
//
//  Created by DongDong on 2019/9/6.
//  Copyright © 2019 qizhi. All rights reserved.
//

#import <Foundation/Foundation.h>
//@class FMResultSet;

NS_ASSUME_NONNULL_BEGIN

/*!
 消息的方向
 */
typedef NS_ENUM(NSUInteger, IMMessageDirection) {
    //发送
    MessageDirection_SEND = 1,
    //接收
    MessageDirection_RECEIVE = 2
};

@interface IMQZMessageModel : NSObject
//消息id 13位时间戳+6位随机码
@property (nonatomic, copy) NSString *msgId;
//消息唯一标签 群:group_msg 单聊:normal_msg
@property (nonatomic, copy) NSString *msgTag;
//消息类型 text=文字；face=表情；pic=图片；file=文件；amr=语音消息；video=视频
@property (nonatomic, copy) NSString *msgType;
//消息的发送状态 -1:发送失败 0:发送中 1:发送成功 2:对方已读（暂不支持）
@property (nonatomic, copy) NSString *sendStatus;

//发送者userid
@property (nonatomic, copy) NSString *senderId;
//发送者名称、昵称、备注名等
@property (nonatomic, copy) NSString *senderName;
//发送者头像
@property (nonatomic, copy) NSString *senderHead;

//群:群组groupid 单聊:不管是收到的消息还是自己发送的消息，此id都是对方userid 
@property (nonatomic, copy) NSString *targetId;
//群:群名称 单聊:对方名称、昵称、备注名等
@property (nonatomic, copy) NSString *targetName;
//群头像
@property (nonatomic, copy) NSString *targetHead;
//群主id 管理员id
@property (nonatomic, copy) NSString *managerId;

//接发消息的时间戳 10位
@property (nonatomic, copy) NSString *time;

//最后一条消息的msgId
@property (nonatomic, copy) NSString *lastMsgId;
//未读消息数量 用于会话列表
@property (nonatomic, copy) NSString *unreadCount;

//消息方向
@property (nonatomic, assign) IMMessageDirection messageDirection;
//消息内容
@property (nonatomic, strong) NSString *content;

//@人的成员数据 "100021|100231|1001231", 如果是0就是@所有人
@property (nonatomic, strong) NSString *atmembers;

//是否为撤回消息
@property (nonatomic, strong) NSString *isRetrive;

//是否打开过 用于红包和语音
@property (nonatomic, copy) NSString *isOpen;
//是否置顶
@property (nonatomic, copy) NSString *isTop;
//是否免打扰 数据保存在服务器 通过好友列表获取
@property (nonatomic, copy) NSString *isDND;
//是否提醒我
@property (nonatomic, copy) NSString *isRemindMe;
//附加内容
@property (nonatomic, copy) NSString *extra;


//时间格式 10:00 昨天等 会话列表和聊天列表的时间逻辑有分别
//聊天列表:小于等于3分钟不显示  大于3分钟小于一天->10:00 大于一天小于2天->昨天 10:00 大于2天 2018年12月19日 10:00
@property (nonatomic, copy) NSString *timeForm;

//加密方式 默认为des加密
@property (nonatomic, copy) NSString *raw;
//是否需要回执 1代表需要回执消息 其它不需要回执
@property (nonatomic, copy) NSString *ack;
//用token拼接上述参数按照既定顺序des加密 （messageid:msgtag:sender:targetid）
@property (nonatomic, copy) NSString *sign;
//是否严格加密
@property (nonatomic, strong) NSString *isStrongEncrypt;
//是否展示昵称
//@property (nonatomic, assign) BOOL isShowNickname;
//是否阅后即焚
//@property (nonatomic, assign) BOOL isReadedFire;
//lastContent 用于会话列表
//@property (nonatomic, copy) NSString *lastContent;

/**
 * @brief json字典转消息模型
 * @param json 服务器收到的消息体
 * @return 返回消息模型
 */
+ (IMQZMessageModel*)getModelWithJson:(NSDictionary*)json;

/**
 * @brief 数据库集合转消息模型
 * @param res 本地存储消息的数据库
 * @return 返回消息模型
 */
//+ (IMQZMessageModel*)getModelWithRes:(FMResultSet*)res;

@end

NS_ASSUME_NONNULL_END
