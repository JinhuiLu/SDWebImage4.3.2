/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

@interface SDImageCacheConfig : NSObject

/**
 * Decompressing images that are downloaded and cached can improve performance but can consume lot of memory.
 * Defaults to YES. Set this to NO if you are experiencing a crash due to excessive memory consumption.
    解压缩图像下载和缓存可以提高性能，但是会消耗大量内存， 默认是YES ，如果因为消耗内存过大而崩溃，可以置为NO。
    是否解压图片，默认YES
 */
@property (assign, nonatomic) BOOL shouldDecompressImages;

/**
 * disable iCloud backup [defaults to YES]
    是否禁用 iCloud 备份，默认是 YES
 */
@property (assign, nonatomic) BOOL shouldDisableiCloud;

/**
 * use memory cache [defaults to YES]
    是否缓存到内存中，默认是YES
 */
@property (assign, nonatomic) BOOL shouldCacheImagesInMemory;

/**
 * The reading options while reading cache from disk.
 * Defaults to 0. You can set this to `NSDataReadingMappedIfSafe` to improve performance.
    读取磁盘缓存时的阅读选项。
 */
@property (assign, nonatomic) NSDataReadingOptions diskCacheReadingOptions;

/**
 * The writing options while writing cache to disk.
 * Defaults to `NSDataWritingAtomic`. You can set this to `NSDataWritingWithoutOverwriting` to prevent overwriting an existing file.
 在将缓存写入磁盘时写入选项。
 */
@property (assign, nonatomic) NSDataWritingOptions diskCacheWritingOptions;

/**
 * The maximum length of time to keep an image in the cache, in seconds.
    在缓存中保存图像的最长时间，以秒为单位。（默认一周）
 */
@property (assign, nonatomic) NSInteger maxCacheAge;

/**
 * The maximum size of the cache, in bytes.
    缓存的最大大小，以字节为单位。
 */
@property (assign, nonatomic) NSUInteger maxCacheSize;

@end
