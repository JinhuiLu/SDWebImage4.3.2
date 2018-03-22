/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "UIView+WebCacheOperation.h"

#if SD_UIKIT || SD_MAC

#import "objc/runtime.h"

static char loadOperationKey;

// key is copy, value is weak because operation instance is retained by SDWebImageManager's runningOperations property
// we should use lock to keep thread-safe because these method may not be acessed from main queue
typedef NSMapTable<NSString *, id<SDWebImageOperation>> SDOperationsDictionary;

@implementation UIView (WebCacheOperation)

- (SDOperationsDictionary *)sd_operationDictionary {
    //我们应该使用锁来保持线程安全，因为这些方法可能不会从主队列中获得。
    @synchronized(self) {
        SDOperationsDictionary *operations = objc_getAssociatedObject(self, &loadOperationKey);
        if (operations) {
            return operations;
        }
        // key是copy，value是weak，因为操作实例被SDWebImageManager的runningOperations属性保留。循环持有
        // NSPointerFunctionsWeakMemory 不会修改MapTable容器内对象元素的引用计数，并且对象释放后，会被自动移除
        operations = [[NSMapTable alloc] initWithKeyOptions:NSPointerFunctionsStrongMemory valueOptions:NSPointerFunctionsWeakMemory capacity:0];
        objc_setAssociatedObject(self, &loadOperationKey, operations, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        return operations;
    }
}

- (void)sd_setImageLoadOperation:(nullable id<SDWebImageOperation>)operation forKey:(nullable NSString *)key {
    if (key) {
        //取消操作
        [self sd_cancelImageLoadOperationWithKey:key];
        //然后把当前传的操作缓存下来
        if (operation) {
            SDOperationsDictionary *operationDictionary = [self sd_operationDictionary];
            @synchronized (self) {
                [operationDictionary setObject:operation forKey:key];
            }
        }
    }
}

- (void)sd_cancelImageLoadOperationWithKey:(nullable NSString *)key {
    // Cancel in progress downloader from queue
    // 从队列中取消进度下载
    SDOperationsDictionary *operationDictionary = [self sd_operationDictionary];
    id<SDWebImageOperation> operation;
    @synchronized (self) {
        // 根据key取出当前的操作
        operation = [operationDictionary objectForKey:key];
    }
    if (operation) {
        //检查是否实现了SDWebImageOperation协议的方法
        if ([operation conformsToProtocol:@protocol(SDWebImageOperation)]){
            [operation cancel];
        }
        @synchronized (self) {
            [operationDictionary removeObjectForKey:key];
        }
    }
}

- (void)sd_removeImageLoadOperationWithKey:(nullable NSString *)key {
    if (key) {
        SDOperationsDictionary *operationDictionary = [self sd_operationDictionary];
        @synchronized (self) {
            [operationDictionary removeObjectForKey:key];
        }
    }
}

@end

#endif
