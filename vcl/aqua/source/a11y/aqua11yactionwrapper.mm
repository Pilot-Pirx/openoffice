/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_vcl.hxx"

#include "aqua/salinst.h"

#include "aqua11yactionwrapper.h"

// Wrapper for XAccessibleAction

@implementation AquaA11yActionWrapper : NSObject

+(NSString *)nativeActionNameFor:(NSString *)actionName {
    // TODO: Optimize ?
    //       Use NSAccessibilityActionDescription
    if ( [ actionName isEqualToString: @"click" ] ) {
        return NSAccessibilityPressAction;
    } else if ( [ actionName isEqualToString: @"togglePopup" ] ) {
        return NSAccessibilityShowMenuAction;
    } else if ( [ actionName isEqualToString: @"select" ] ) {
        return NSAccessibilityPickAction;
    } else if ( [ actionName isEqualToString: @"incrementLine" ] ) {
        return NSAccessibilityIncrementAction;
    } else if ( [ actionName isEqualToString: @"decrementLine" ] ) {
        return NSAccessibilityDecrementAction;
    } else if ( [ actionName isEqualToString: @"incrementBlock" ] ) {
        return NSAccessibilityIncrementAction; // TODO ?
    } else if ( [ actionName isEqualToString: @"decrementBlock" ] ) {
        return NSAccessibilityDecrementAction; // TODO ?
    } else if ( [ actionName isEqualToString: @"Browse" ] ) {
        return NSAccessibilityPressAction; // TODO ?
    } else {
        return [ NSString string ];
    }
}

+(NSArray *)actionNamesForElement:(AquaA11yWrapper *)wrapper {
    NSMutableArray * actionNames = [ [ NSMutableArray alloc ] init ];
    if ( [ wrapper accessibleAction ] != nil ) {
        for ( int cnt = 0; cnt < [ wrapper accessibleAction ] -> getAccessibleActionCount(); cnt++ ) {
            [ actionNames addObject: [ AquaA11yActionWrapper nativeActionNameFor: CreateNSString ( [ wrapper accessibleAction ] -> getAccessibleActionDescription ( cnt ) ) ] ];
        }
    }
    return actionNames;
}

+(void)doAction:(NSString *)action ofElement:(AquaA11yWrapper *)wrapper {
    if ( [ wrapper accessibleAction ] != nil ) {
        for ( int cnt = 0; cnt < [ wrapper accessibleAction ] -> getAccessibleActionCount(); cnt++ ) {
            if ( [ action isEqualToString: [ AquaA11yActionWrapper nativeActionNameFor: CreateNSString ( [ wrapper accessibleAction ] -> getAccessibleActionDescription ( cnt ) ) ] ] ) {
                [ wrapper accessibleAction ] -> doAccessibleAction ( cnt );
                break;
            }
        }
    }
}

@end