//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_BBOX_HEADER
#define CC_BBOX_HEADER

//CCLib
#include <CCGeom.h>
#include <Matrix.h>

#include "ccGLMatrix.h"
#include "ccBasicTypes.h"

//! Bounding box structure
/** Supports several operators such addition (to a matrix or a vector) and
    multiplication (by a matrix or a scalar).
**/
#ifdef QCC_DB_USE_AS_DLL
#include "qCC_db.h"
class QCC_DB_LIB_API ccBBox
#else
class ccBBox
#endif
{
public:

    //! Default constructor
    ccBBox();
    //! Copy constructor
    ccBBox(const ccBBox& aBBox);
    //! Constructor from two vectors (lower min. and upper max. corners)
    ccBBox(const CCVector3 &bbMinCorner, const CCVector3 &bbMaxCorner);

    //! Returns the 'sum' of this bounding-box and another one
    ccBBox operator + (const ccBBox& aBBox) const;
    //! In place 'sum' of this bounding-box with another one
    const ccBBox& operator += (const ccBBox& aBBox);
    //! Shifts the bounding box with a vector
    const ccBBox& operator += (const CCVector3& aVector);
    //! Shifts the bounding box with a vector
    const ccBBox& operator -= (const CCVector3& aVector);
    //! Scales the bounding box
    const ccBBox& operator *= (const PointCoordinateType& scaleFactor);
    //! Rotates the bounding box
    const ccBBox& operator *= (const CCLib::SquareMatrix& aMatrix);
    //! Applies transformation to the bounding box
    const ccBBox& operator *= (const ccGLMatrix& mat);

    //! Resets the bounding box
    /** (0,0,0) --> (0,0,0)
    **/
    void clear();

    //! 'Enlarges' the bounding box with a vector
    /** equivalent to operator +=(CCVector3)
    **/
    void add(const CCVector3& aVector);

    //! Returns min corner (const)
    inline const CCVector3& minCorner() const { return m_bbMin; }
    //! Returns max corner (const)
    inline const CCVector3& maxCorner() const { return m_bbMax; }

    //! Returns min corner
	inline CCVector3& minCorner() { return m_bbMin; }
    //! Returns max corner
    inline CCVector3& maxCorner() { return m_bbMax; }

    //! Returns center
    CCVector3 getCenter() const;
    //! Returns diagonal vector
    CCVector3 getDiagVec() const;
    //! Returns diagonal length
    PointCoordinateType getDiagNorm() const;
	//! Returns minimal box dimension
	PointCoordinateType getMinBoxDim() const;
	//! Returns maximal box dimension
	PointCoordinateType getMaxBoxDim() const;

    //! Draws bounding box (OpenGL)
    /** \param col (R,G,B) color
    **/
    void draw(const colorType col[]) const;

    //! Sets bonding box validity
	inline void setValidity(bool state) { m_valid = state; }

    //! Returns whether bounding box is valid or not
	inline bool isValid() const { return m_valid; }

	//! Computes min gap (absolute distance) between this bounding-box and another one
	/** \return min gap (>=0) or -1 if at least one of the box is not valid
	**/
	PointCoordinateType minDistTo(const ccBBox& box) const;

	//! Returns whether a points is inside the box or not
	/** Warning: box should be valid!
	**/
	inline bool contains(const CCVector3& P) const
	{
		return (P.x >= m_bbMin.x && P.x <= m_bbMax.x &&
				P.y >= m_bbMin.y && P.y <= m_bbMax.y &&
				P.z >= m_bbMin.z && P.z <= m_bbMax.z);
	}

protected:

    //! Lower min. corner
    CCVector3 m_bbMin;
    //! Upper max. corner
    CCVector3 m_bbMax;
    //! Validity
    bool m_valid;
};

#endif //CC_BBOX_HEADER
