//
//  GAOCSqliteManager.h
//  GXEngineELSqlite3ForMacOS
//
//  Created by Gu Gengxin on 12-3-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "sqlite3.h"

extern NSString* const gxvSqliteManagerTableKey_Name;
extern NSString* const gxvSqliteManagerTableKey_Fields;

extern NSString* const gxvSqliteManagerFieldKey_ID;
extern NSString* const gxvSqliteManagerFieldKey_Name;
extern NSString* const gxvSqliteManagerFieldKey_Type;
extern NSString* const gxvSqliteManagerFieldKey_NotNull;
extern NSString* const gxvSqliteManagerFieldKey_DefaultValue;
extern NSString* const gxvSqliteManagerFieldKey_PK;

extern NSString* const gxvSqliteManagerFieldType_Text;
extern NSString* const gxvSqliteManagerFieldType_Integer;
extern NSString* const gxvSqliteManagerFieldType_Numeric;
extern NSString* const gxvSqliteManagerFieldType_Blob;
extern NSString* const gxvSqliteManagerFieldType_PK;
extern NSString* const gxvSqliteManagerFieldType_NotNull;



@interface GAOCSqliteManager : NSObject {
    
    sqlite3* sqlDB;
	NSCondition* cinLock;
}

@property (nonatomic,readonly) sqlite3* sqlDB;
@property (nonatomic,readonly) NSArray* tables;


- (BOOL)open:(NSString*)ssDBPath;
- (void)close;

- (void)keyInput:(NSString*)ssKey;
- (void)keySet:(NSString*)ssKey;

- (NSArray*)tableNames;
- (NSArray*)fieldsOfTable:(NSString*)ssTableName;

- (BOOL)addFieldAtTable:(NSString*)ssTableName 
				  withName:(NSString*)ssName 
					  type:(NSString*)ssType
				primaryKey:(BOOL)bPK
				   notNull:(BOOL)bNotNull
		   andDefaultValue:(NSString*)ssDefValue;
- (BOOL)addFieldAtTable:(NSString*)ssTableName withField:(NSDictionary*)dicField;
- (BOOL)createTable:(NSString*)ssTableName withFields:(NSArray*)arrFields;
- (NSString*)sqlStatementOfField:(NSDictionary*)dicField;

- (sqlite3_stmt*)readyWithSQL:(NSString*)ssSQLStatement;
- (void)done:(sqlite3_stmt*)pStmt;
- (NSString*)getText:(sqlite3_stmt*)pStmt withColumn:(int)nColumnNum;
- (NSData*)getData:(sqlite3_stmt*)pStmt withColumn:(int)nColumnNum;

- (NSMutableDictionary*)loadDataWithTable:(NSDictionary*)dicTable keyValues:(NSDictionary*)dicKV;
- (NSMutableArray*)loadDataAllWithTable:(NSDictionary*)dicTable keyValues:(NSDictionary*)dicKV;
- (BOOL)checkDataTable:(NSDictionary*)dicTable andOnlyPrimaryValue:(NSDictionary*)dicValue;
- (BOOL)saveDataWithTable:(NSDictionary*)dicTable andValue:(NSDictionary*)dicValue outIsNew:(BOOL*)pIsNew;
- (BOOL)deleteDataWithTable:(NSDictionary*)dicTable andValue:(NSDictionary*)dicValue onlyPrimary:(BOOL)onlyPri;

@end

@interface GAOCSqliteManager (DBCheck)

+ (BOOL)checkDBAtDocument:(NSString*)ssDBName copyFromMainBundle:(BOOL)bCopy;
+ (BOOL)checkDB:(GAOCSqliteManager*)iSMTo addFromDB:(GAOCSqliteManager*)iSMFrom;

@end
