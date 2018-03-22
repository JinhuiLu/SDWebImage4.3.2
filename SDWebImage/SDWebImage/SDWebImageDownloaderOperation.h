/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageDownloader.h"
#import "SDWebImageOperation.h"

//开始下载通知
FOUNDATION_EXPORT NSString * _Nonnull const SDWebImageDownloadStartNotification;

//收到response通知
FOUNDATION_EXPORT NSString * _Nonnull const SDWebImageDownloadReceiveResponseNotification;

//停止下载通知
FOUNDATION_EXPORT NSString * _Nonnull const SDWebImageDownloadStopNotification;

//结束下载通知
FOUNDATION_EXPORT NSString * _Nonnull const SDWebImageDownloadFinishNotification;



/**
 Describes a downloader operation. If one wants to use a custom downloader op, it needs to inherit from `NSOperation` and conform to this protocol
 For the description about these methods, see `SDWebImageDownloaderOperation`
 */
//如果我们想要使用一个自定义的下载操作，那么这个对象需要继承自NSOperation，并且实现这个协议
@protocol SDWebImageDownloaderOperationInterface<NSObject>

//SDWebImageDownloaderOperationInterface的初始化方法
- (nonnull instancetype)initWithRequest:(nullable NSURLRequest *)request
                              inSession:(nullable NSURLSession *)session
                                options:(SDWebImageDownloaderOptions)options;

//绑定DownloaderOperation的下载进度block和结束block
- (nullable id)addHandlersForProgress:(nullable SDWebImageDownloaderProgressBlock)progressBlock
                            completed:(nullable SDWebImageDownloaderCompletedBlock)completedBlock;

//返回当前下载操作的图片是否应该压缩
- (BOOL)shouldDecompressImages;
//设置是否应该压缩图片
- (void)setShouldDecompressImages:(BOOL)value;
//返回身份认证
- (nullable NSURLCredential *)credential;
//设置身份认证
- (void)setCredential:(nullable NSURLCredential *)value;

- (BOOL)cancel:(nullable id)token;

@end


@interface SDWebImageDownloaderOperation : NSOperation <SDWebImageDownloaderOperationInterface, SDWebImageOperation, NSURLSessionTaskDelegate, NSURLSessionDataDelegate>

/**
 * The request used by the operation's task.
 */
//operation的请求request
@property (strong, nonatomic, readonly, nullable) NSURLRequest *request;

/**
 * The operation's task
 */
//operation的task
@property (strong, nonatomic, readonly, nullable) NSURLSessionTask *dataTask;


@property (assign, nonatomic) BOOL shouldDecompressImages;

/**
 *  Was used to determine whether the URL connection should consult the credential storage for authenticating the connection.
 *  @deprecated Not used for a couple of versions
 */
@property (nonatomic, assign) BOOL shouldUseCredentialStorage __deprecated_msg("Property deprecated. Does nothing. Kept only for backwards compatibility");

/**
 * The credential used for authentication challenges in `-URLSession:task:didReceiveChallenge:completionHandler:`.
 *
 * This will be overridden by any shared credentials that exist for the username or password of the request URL, if present.
 */
//身份认证
@property (nonatomic, strong, nullable) NSURLCredential *credential;

/**
 * The SDWebImageDownloaderOptions for the receiver.
 */
//下载配置策略
@property (assign, nonatomic, readonly) SDWebImageDownloaderOptions options;

/**
 * The expected size of data.
 */
//期望data的大小size
@property (assign, nonatomic) NSInteger expectedSize;

/**
 * The response returned by the operation's task.
 */
//operation的response
@property (strong, nonatomic, nullable) NSURLResponse *response;

/**
 *  Initializes a `SDWebImageDownloaderOperation` object
 *
 *  @see SDWebImageDownloaderOperation
 *
 *  @param request        the URL request
 *  @param session        the URL session in which this operation will run
 *  @param options        downloader options
 *
 *  @return the initialized instance
 */
//初始化一个SDWebImageDownloaderOperation对象
- (nonnull instancetype)initWithRequest:(nullable NSURLRequest *)request
                              inSession:(nullable NSURLSession *)session
                                options:(SDWebImageDownloaderOptions)options NS_DESIGNATED_INITIALIZER;

/**
 *  Adds handlers for progress and completion. Returns a tokent that can be passed to -cancel: to cancel this set of
 *  callbacks.
 *
 *  @param progressBlock  the block executed when a new chunk of data arrives.
 *                        @note the progress block is executed on a background queue
 *  @param completedBlock the block executed when the download is done.
 *                        @note the completed block is executed on the main queue for success. If errors are found, there is a chance the block will be executed on a background queue
 *
 *  @return the token to use to cancel this set of handlers
 */
//绑定DownloaderOperation的下载进度block和结束block
- (nullable id)addHandlersForProgress:(nullable SDWebImageDownloaderProgressBlock)progressBlock
                            completed:(nullable SDWebImageDownloaderCompletedBlock)completedBlock;

/**
 *  Cancels a set of callbacks. Once all callbacks are canceled, the operation is cancelled.
 *
 *  @param token the token representing a set of callbacks to cancel
 *
 *  @return YES if the operation was stopped because this was the last token to be canceled. NO otherwise.
 */
//SDWebImageOperation的协议方法
- (BOOL)cancel:(nullable id)token;

@end
