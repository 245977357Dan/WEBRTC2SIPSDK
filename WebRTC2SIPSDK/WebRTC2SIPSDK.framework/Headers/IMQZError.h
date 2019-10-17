//
//  IMQZError.h
//  QzIMLib
//
//  Created by DongDong on 2019/8/16.
//  Copyright © 2019 qizhi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface IMQZError : NSObject
/*
 错误码
 0000:连接成功 登录成功
 0001:失败
 0002:连接失败
 0003:appid错误
 0004:登录失败
 0005:服务器错误
 0006:网络错误
 0007:参数错误
 0008:正在通话中，或者正在录音，呼叫失败
 */
@property (nonatomic, copy) NSString *errorCode;

//错误信息描述
@property (nonatomic, copy) NSString *errorInfo;

//附加参数
@property (nonatomic, strong) id extra;

+ (IMQZError*)errorWithCode:(NSString*)code info:(NSString*)info;
@end

NS_ASSUME_NONNULL_END
