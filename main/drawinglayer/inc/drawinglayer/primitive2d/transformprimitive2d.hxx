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



#ifndef INCLUDED_DRAWINGLAYER_PRIMITIVE2D_TRANSFORMPRIMITIVE2D_HXX
#define INCLUDED_DRAWINGLAYER_PRIMITIVE2D_TRANSFORMPRIMITIVE2D_HXX

#include <drawinglayer/drawinglayerdllapi.h>
#include <drawinglayer/primitive2d/groupprimitive2d.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
        /** TransformPrimitive2D class

            This is one of the basic grouping primitives and it provides
            embedding a sequence of primitives (a geometry) into a
            transformation. All renderers have to handle this, usually by
            building a current transformation stack (linear combination)
            and applying this to all to-be-rendered geometry. If not handling
            this, the output will be mostly wrong since this primitive is
            widely used.

            It does transform by embedding an existing geometry into a
            transformation as Child-content. This allows re-usage of the
            refcounted Uno-Api primitives and their existung, buffered
            decompositions.
            
            It could e.g. be used to show a single object geometry in 1000 
            different, transformed states without the need to create those 
            thousand primitive contents.
         */
		class DRAWINGLAYER_DLLPUBLIC TransformPrimitive2D : public GroupPrimitive2D
		{
		private:
            // the transformation to apply to the child geometry
			basegfx::B2DHomMatrix					maTransformation;

		public:
            /// constructor
			TransformPrimitive2D(
				const basegfx::B2DHomMatrix& rTransformation, 
				const Primitive2DSequence& rChildren);

			/// data read access
			const basegfx::B2DHomMatrix& getTransformation() const { return maTransformation; }

			/// compare operator
			virtual bool operator==(const BasePrimitive2D& rPrimitive) const;

			/// get range
			virtual basegfx::B2DRange getB2DRange(const geometry::ViewInformation2D& rViewInformation) const;

			/// provide unique ID
			DeclPrimitrive2DIDBlock()
		};
	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

#endif //INCLUDED_DRAWINGLAYER_PRIMITIVE2D_TRANSFORMPRIMITIVE2D_HXX

//////////////////////////////////////////////////////////////////////////////
// eof
