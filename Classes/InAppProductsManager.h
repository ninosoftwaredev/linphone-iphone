/* InAppProductsManager.h
 *
 * Copyright (C) 2012  Belledonne Comunications, Grenoble, France
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#import <XMLRPCConnectionDelegate.h>

extern NSString *const kLinphoneIAPurchaseNotification;

@interface InAppProductsXMLRPCDelegate : NSObject <XMLRPCConnectionDelegate>

@end

@interface InAppProductsManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver> {
	NSString *latestReceiptMD5;
}

// startup status, manager is not ready yet.
#define IAPNotReadyYet			@"IAPNotReadyYet"
#define IAPAvailableSucceeded	@"IAPAvailableSucceeded"
#define IAPAvailableFailed		@"IAPAvailableFailed"
#define IAPPurchaseFailed		@"IAPPurchaseFailed"
#define IAPPurchaseSucceeded	@"IAPPurchaseSucceeded"
#define IAPRestoreFailed		@"IAPRestoreFailed"
#define IAPRestoreSucceeded		@"IAPRestoreSucceeded"
#define IAPReceiptFailed		@"IAPReceiptFailed"
#define IAPReceiptSucceeded		@"IAPReceiptSucceeded"

typedef NSString*               IAPPurchaseNotificationStatus;

// needed because request:didFailWithError method is already used by SKProductsRequestDelegate...
@property (nonatomic, retain) InAppProductsXMLRPCDelegate *xmlrpc;

@property (nonatomic, retain) IAPPurchaseNotificationStatus status;
@property (nonatomic, copy) NSString *errlast;

@property (nonatomic, strong) NSMutableArray *productsAvailable;
@property (nonatomic, strong) NSMutableArray *productsIDPurchased;


- (BOOL)isPurchasedWithID:(NSString*)productId;
- (void)purchaseWithID:(NSString*)productId;
// restore user purchases. Must be a user action ONLY.
- (void)restore;
- (void)retrievePurchases;
// internal API only due to methods conflict
- (void)XMLRPCRequest:(XMLRPCRequest *)request didReceiveResponse:(XMLRPCResponse *)response;
// internal API only due to methods conflict
- (void)XMLRPCRequest:(XMLRPCRequest *)request didFailWithError:(NSError *)error;

@end
