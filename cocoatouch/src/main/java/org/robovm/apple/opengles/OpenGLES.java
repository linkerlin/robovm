/*
 * Copyright (C) 2014 Trillian Mobile AB
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.robovm.apple.opengles;

/*<imports>*/
import java.io.*;
import java.nio.*;
import java.util.*;
import org.robovm.objc.*;
import org.robovm.objc.annotation.*;
import org.robovm.objc.block.*;
import org.robovm.rt.*;
import org.robovm.rt.bro.*;
import org.robovm.rt.bro.annotation.*;
import org.robovm.rt.bro.ptr.*;
import org.robovm.apple.foundation.*;
/*</imports>*/

/*<javadoc>*/
/*</javadoc>*/
/*<annotations>*/@Library("OpenGLES")/*</annotations>*/
/*<visibility>*/public/*</visibility>*/ class /*<name>*/OpenGLES/*</name>*/ 
    extends /*<extends>*/Object/*</extends>*/ 
    /*<implements>*//*</implements>*/ {

    /*<ptr>*/
    /*</ptr>*/
    /*<bind>*/static { Bro.bind(OpenGLES.class); }/*</bind>*/
    /*<constants>*//*</constants>*/
    /*<constructors>*//*</constructors>*/
    /*<properties>*//*</properties>*/
    /*<members>*//*</members>*/
    
    public static int getMajorVersion() {
        IntPtr major = new IntPtr();
        IntPtr minor = new IntPtr();
        getVersion(major, minor);
        return major.get();
    }

    public static int getMinorVersion() {
        IntPtr major = new IntPtr();
        IntPtr minor = new IntPtr();
        getVersion(major, minor);
        return minor.get();
    }
    
    /*<methods>*/
    @GlobalValue(symbol="kEAGLDrawablePropertyRetainedBacking", optional=true)
    public static native NSString DrawablePropertyRetainedBacking();
    @GlobalValue(symbol="kEAGLDrawablePropertyColorFormat", optional=true)
    public static native NSString DrawablePropertyColorFormat();
    @GlobalValue(symbol="kEAGLColorFormatRGBA8", optional=true)
    public static native NSString ColorFormatRGBA8();
    @GlobalValue(symbol="kEAGLColorFormatRGB565", optional=true)
    public static native NSString ColorFormatRGB565();
    /**
     * @since Available in iOS 7.0 and later.
     */
    @GlobalValue(symbol="kEAGLColorFormatSRGBA8", optional=true)
    public static native NSString ColorFormatSRGBA8();
    
    @Bridge(symbol="EAGLGetVersion", optional=true)
    protected static native void getVersion(IntPtr major, IntPtr minor);
    /*</methods>*/
}
