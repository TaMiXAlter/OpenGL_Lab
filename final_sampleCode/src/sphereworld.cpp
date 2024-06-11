// SphereWorld.cpp
// OpenGL SuperBible
// Demonstrates an immersive 3D environment using actors
// and a camera. This version adds lights and material properties
// and shadows.
// Program by Richard S. Wright Jr.

#include <cstdio>
#include <GL/gl.h>
#include <cmath>
#include <math3d.h>
#include "freeglut_std.h"
/**Math 3D*/
/**cross product*/
inline void m3dCrossProduct(M3DVector3f result, const M3DVector3f u, const M3DVector3f v)
{
	result[0] = u[1]*v[2] - v[1]*u[2];
	result[1] = -u[0]*v[2] + v[0]*u[2];
	result[2] = u[0]*v[1] - v[0]*u[1];
}
/**normal*/
inline float m3dGetVectorLengthSquared(const M3DVector3f u)
{ return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }
inline float m3dGetVectorLength(const M3DVector3f u)
{ return float(sqrt(double(m3dGetVectorLengthSquared(u)))); }
inline void m3dNormalizeVector(M3DVector3f u)
{ m3dScaleVector3(u, 1.0f / m3dGetVectorLength(u)); }


/**gl tool*/
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat){
    FILE *pFile;			// File pointer
    TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte	*pBits = NULL;          // Pointer to bits

    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;

    // Attempt to open the file
    pFile = fopen(szFileName, "rb");
    if(pFile == NULL)
    {
        printf("File not found");
        return NULL;
	}
    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

    // Do byte swap for big vs little endian
#ifdef __APPLE__
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif

    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;

    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;

    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;

    // Read in the bits
    // Check for read error. This should catch RLE or other
    // weird formats that I don't want to recognize
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        free(pBits);
        return NULL;
		}

    // Set OpenGL format expected
    switch(sDepth)
		{
        case 3:     // Most likely case
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB8;
            break;
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA8;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE8;
            break;
		};
    // Done with File
    fclose(pFile);

    // Return pointer to image data
    return pBits;
}
void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
	GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;     // Looping variables

	for (i = 0; i < iStacks; i++)
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

		// Many sources of OpenGL sphere drawing code uses a triangle fan
		// for the caps of the sphere. This however introduces texturing
		// artifacts at the poles on some OpenGL implementations
		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for ( j = 0; j <= iSlices; j++)
		{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;

			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();

		t -= dt;
	}
}
void gltDrawTorus(GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor)
{
	M3DVector3f vNormal;
	double majorStep = 2.0f*M3D_PI / numMajor;
	double minorStep = 2.0f*M3D_PI / numMinor;
	int i, j;

	for (i=0; i<numMajor; ++i)
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat) cos(a0);
		GLfloat y0 = (GLfloat) sin(a0);
		GLfloat x1 = (GLfloat) cos(a1);
		GLfloat y1 = (GLfloat) sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j=0; j<=numMinor; ++j)
		{
			double b = j * minorStep;
			GLfloat c = (GLfloat) cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat) sin(b);

			// First point
			glTexCoord2f((float)(i)/(float)(numMajor), (float)(j)/(float)(numMinor));
			vNormal[0] = x0*c;
			vNormal[1] = y0*c;
			vNormal[2] = z/minorRadius;
			m3dNormalizeVector(vNormal);
			glNormal3fv(vNormal);
			glVertex3f(x0*r, y0*r, z);

			glTexCoord2f((float)(i+1)/(float)(numMajor), (float)(j)/(float)(numMinor));
			vNormal[0] = x1*c;
			vNormal[1] = y1*c;
			vNormal[2] = z/minorRadius;
			m3dNormalizeVector(vNormal);
			glNormal3fv(vNormal);
			glVertex3f(x1*r, y1*r, z);
		}
		glEnd();
	}
}

/**GLFrame*/
class GLFrame
    {
	protected:
        M3DVector3f vOrigin;	// Where am I?
        M3DVector3f vForward;	// Where am I going?
        M3DVector3f vUp;		// Which way is up?

    public:
		// Default position and orientation. At the origin, looking
		// down the positive Z axis (right handed coordinate system).
		GLFrame(void) {
			// At origin
            vOrigin[0] = 0.0f; vOrigin[1] = 0.0f; vOrigin[2] = 0.0f;

			// Up is up (+Y)
            vUp[0] = 0.0f; vUp[1] = 1.0f; vUp[2] = 0.0f;

			// Forward is -Z (default OpenGL)
            vForward[0] = 0.0f; vForward[1] = 0.0f; vForward[2] = -1.0f;
            }


        /////////////////////////////////////////////////////////////
        // Set Location
        inline void SetOrigin(const M3DVector3f vPoint) {
			m3dCopyVector3(vOrigin, vPoint); }

        inline void SetOrigin(float x, float y, float z) {
			vOrigin[0] = x; vOrigin[1] = y; vOrigin[2] = z; }

		inline void GetOrigin(M3DVector3f vPoint) {
			m3dCopyVector3(vPoint, vOrigin); }

		inline float GetOriginX(void) { return vOrigin[0]; }
		inline float GetOriginY(void) { return vOrigin[1]; }
		inline float GetOriginZ(void) { return vOrigin[2]; }

        /////////////////////////////////////////////////////////////
        // Set Forward Direction
        inline void SetForwardVector(const M3DVector3f vDirection) {
			m3dCopyVector3(vForward, vDirection); }

        inline void SetForwardVector(float x, float y, float z)
            { vForward[0] = x; vForward[1] = y; vForward[2] = z; }

        inline void GetForwardVector(M3DVector3f vVector) { m3dCopyVector3(vVector, vForward); }

        /////////////////////////////////////////////////////////////
        // Set Up Direction
        inline void SetUpVector(const M3DVector3f vDirection) {
			m3dCopyVector3(vUp, vDirection); }

        inline void SetUpVector(float x, float y, float z)
			{ vUp[0] = x; vUp[1] = y; vUp[2] = z; }

        inline void GetUpVector(M3DVector3f vVector) { m3dCopyVector3(vVector, vUp); }


		/////////////////////////////////////////////////////////////
		// Get Axes
		inline void GetZAxis(M3DVector3f vVector) { GetForwardVector(vVector); }
		inline void GetYAxis(M3DVector3f vVector) { GetUpVector(vVector); }
		inline void GetXAxis(M3DVector3f vVector) { m3dCrossProduct(vVector, vUp, vForward); }


		/////////////////////////////////////////////////////////////
        // Translate along orthonormal axis... world or local
        inline void TranslateWorld(float x, float y, float z)
			{ vOrigin[0] += x; vOrigin[1] += y; vOrigin[2] += z; }

        inline void TranslateLocal(float x, float y, float z)
			{ MoveForward(z); MoveUp(y); MoveRight(x);	}


		/////////////////////////////////////////////////////////////
		// Move Forward (along Z axis)
		inline void MoveForward(float fDelta)
			{
		    // Move along direction of front direction
			vOrigin[0] += vForward[0] * fDelta;
			vOrigin[1] += vForward[1] * fDelta;
			vOrigin[2] += vForward[2] * fDelta;
			}

		// Move along Y axis
		inline void MoveUp(float fDelta)
			{
		    // Move along direction of up direction
			vOrigin[0] += vUp[0] * fDelta;
			vOrigin[1] += vUp[1] * fDelta;
			vOrigin[2] += vUp[2] * fDelta;
			}

		// Move along X axis
		inline void MoveRight(float fDelta)
			{
			// Move along direction of right vector
			M3DVector3f vCross;
			m3dCrossProduct(vCross, vUp, vForward);

			vOrigin[0] += vCross[0] * fDelta;
			vOrigin[1] += vCross[1] * fDelta;
			vOrigin[2] += vCross[2] * fDelta;
			}
		///////////////////////////////////////////////////////////////////////
		// Just assemble the matrix
		void GetMatrix(M3DMatrix44f	matrix, bool bRotationOnly = false)
			{
			// Calculate the right side (x) vector, drop it right into the matrix
			M3DVector3f vXAxis;
			m3dCrossProduct(vXAxis, vUp, vForward);

			// Set matrix column does not fill in the fourth value...
            m3dSetMatrixColumn44(matrix, vXAxis, 0);
            matrix[3] = 0.0f;

            // Y Column
			m3dSetMatrixColumn44(matrix, vUp, 1);
            matrix[7] = 0.0f;

            // Z Column
			m3dSetMatrixColumn44(matrix, vForward, 2);
            matrix[11] = 0.0f;

            // Translation (already done)
			if(bRotationOnly == true)
				{
				matrix[12] = 0.0f;
				matrix[13] = 0.0f;
				matrix[14] = 0.0f;
				}
			else
				m3dSetMatrixColumn44(matrix, vOrigin, 3);

            matrix[15] = 1.0f;
			}


        /////////////////////////////////////////////////////////////
        // Get a 4x4 transformation matrix that describes the ccamera
        // orientation.
        inline void GetCameraOrientation(M3DMatrix44f m)
            {
			M3DVector3f x, z;

			// Make rotation matrix
			// Z vector is reversed
			z[0] = -vForward[0];
			z[1] = -vForward[1];
			z[2] = -vForward[2];

			// X vector = Y cross Z
			m3dCrossProduct(x, vUp, z);

			// Matrix has no translation information and is
			// transposed.... (rows instead of columns)
			#define M(row,col)  m[col*4+row]
			   M(0, 0) = x[0];
			   M(0, 1) = x[1];
			   M(0, 2) = x[2];
			   M(0, 3) = 0.0;
			   M(1, 0) = vUp[0];
			   M(1, 1) = vUp[1];
			   M(1, 2) = vUp[2];
			   M(1, 3) = 0.0;
			   M(2, 0) = z[0];
			   M(2, 1) = z[1];
			   M(2, 2) = z[2];
			   M(2, 3) = 0.0;
			   M(3, 0) = 0.0;
			   M(3, 1) = 0.0;
			   M(3, 2) = 0.0;
			   M(3, 3) = 1.0;
			#undef M
            }


		/////////////////////////////////////////////////////////////
		// Perform viewing or modeling transformations
		// Position as the camera (for viewing). Apply this transformation
		// first as your viewing transformation
		// The default implementation of gluLookAt can be considerably sped up
		// since it uses doubles for everything... then again profile before you
		// tune... ;-) You might get a boost form page fault reduction too... if
		// no other glu routines are used...
		// This will get called once per frame.... go ahead and inline
        inline void ApplyCameraTransform(bool bRotOnly = false)
			{
			M3DMatrix44f m;

            GetCameraOrientation(m);

			// Camera Transform
			glMultMatrixf(m);

			// If Rotation only, then do not do the translation
			if(!bRotOnly)
				glTranslatef(-vOrigin[0], -vOrigin[1], -vOrigin[2]);

			/*gluLookAt(vOrigin[0], vOrigin[1], vOrigin[2],
						vOrigin[0] + vForward[0],
						vOrigin[1] + vForward[1],
						vOrigin[2] + vForward[2],
						vUp[0], vUp[1], vUp[2]);
			*/
			}


		// Position as an object in the scene. This places and orients a
		// coordinate frame for other objects (besides the camera)
		// There is ample room for optimization here...
		// This is going to be called alot... don't inline
		// Add flag to perform actor rotation only and not the translation
        void ApplyActorTransform(bool bRotationOnly = false)
			{
			M3DMatrix44f rotMat;

			GetMatrix(rotMat, bRotationOnly);

			// Apply rotation to the current matrix
			glMultMatrixf(rotMat);
			}


        // Rotate around local X Axes - Note all rotations are in radians
        void RotateLocalX(float fAngle)
			{
			M3DMatrix44f rotMat;
			M3DVector3f vCross;
			m3dCrossProduct(vCross, vUp, vForward);
			m3dRotationMatrix44(rotMat, fAngle,
							vCross[0], vCross[1], vCross[2]);

			M3DVector3f newVect;
			// Inline 3x3 matrix multiply for rotation only
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];
			m3dCopyVector3(vForward, newVect);

			// Update pointing up vector
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];
			m3dCopyVector3(vUp, newVect);
			}

		// Rotate around local Y
        void RotateLocalY(float fAngle)
			{
	        M3DMatrix44f rotMat;

			// Just Rotate around the up vector
			// Create a rotation matrix around my Up (Y) vector
			m3dRotationMatrix44(rotMat, fAngle,
                         vUp[0], vUp[1], vUp[2]);

			M3DVector3f newVect;

	        // Rotate forward pointing vector (inlined 3x3 transform)
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];
			m3dCopyVector3(vForward, newVect);
			}


		// Rotate around local Z
        void RotateLocalZ(float fAngle)
			{
			M3DMatrix44f rotMat;

			// Only the up vector needs to be rotated
			m3dRotationMatrix44(rotMat, fAngle,
							vForward[0], vForward[1], vForward[2]);

			M3DVector3f newVect;
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];
			m3dCopyVector3(vUp, newVect);
			}


		// Reset axes to make sure they are orthonormal. This should be called on occasion
		// if the matrix is long-lived and frequently transformed.
		void Normalize(void)
			{
			M3DVector3f vCross;

			// Calculate cross product of up and forward vectors
			m3dCrossProduct(vCross, vUp, vForward);

			// Use result to recalculate forward vector
			m3dCrossProduct(vForward, vCross, vUp);

			// Also check for unit length...
			m3dNormalizeVector(vUp);
			m3dNormalizeVector(vForward);
			}


		// Rotate in world coordinates...
		void RotateWorld(float fAngle, float x, float y, float z)
			{
            M3DMatrix44f rotMat;

			// Create the Rotation matrix
			m3dRotationMatrix44(rotMat, fAngle, x, y, z);

			M3DVector3f newVect;

			// Transform the up axis (inlined 3x3 rotation)
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];
			m3dCopyVector3(vUp, newVect);

			// Transform the forward axis
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];
			m3dCopyVector3(vForward, newVect);
            }


        // Rotate around a local axis
        void RotateLocal(float fAngle, float x, float y, float z)
            {
            M3DVector3f vWorldVect;
			M3DVector3f vLocalVect;
			m3dLoadVector3(vLocalVect, x, y, z);

            LocalToWorld(vLocalVect, vWorldVect);
            RotateWorld(fAngle, vWorldVect[0], vWorldVect[1], vWorldVect[2]);
            }


		// Convert Coordinate Systems
        // This is pretty much, do the transformation represented by the rotation
        // and position on the point
		// Is it better to stick to the convention that the destination always comes
		// first, or use the conventions that "sounds" like the function...
        void LocalToWorld(const M3DVector3f vLocal, M3DVector3f vWorld)
            {
             // Create the rotation matrix based on the vectors
			M3DMatrix44f rotMat;

			GetMatrix(rotMat, true);

			// Do the rotation (inline it, and remove 4th column...)
			vWorld[0] = rotMat[0] * vLocal[0] + rotMat[4] * vLocal[1] + rotMat[8] *  vLocal[2];
			vWorld[1] = rotMat[1] * vLocal[0] + rotMat[5] * vLocal[1] + rotMat[9] *  vLocal[2];
			vWorld[2] = rotMat[2] * vLocal[0] + rotMat[6] * vLocal[1] + rotMat[10] * vLocal[2];

            // Translate the point
            vWorld[0] += vOrigin[0];
            vWorld[1] += vOrigin[1];
            vWorld[2] += vOrigin[2];
            }

		// Change world coordinates into "local" coordinates
        void WorldToLocal(const M3DVector3f vWorld, M3DVector3f vLocal)
            {
			////////////////////////////////////////////////
            // Translate the origin
			M3DVector3f vNewWorld;
            vNewWorld[0] = vWorld[0] - vOrigin[0];
            vNewWorld[1] = vWorld[1] - vOrigin[1];
            vNewWorld[2] = vWorld[2] - vOrigin[2];

            // Create the rotation matrix based on the vectors
			M3DMatrix44f rotMat;
            M3DMatrix44f invMat;
			GetMatrix(rotMat, true);

			// Do the rotation based on inverted matrix
            m3dInvertMatrix44(invMat, rotMat);

			vLocal[0] = invMat[0] * vNewWorld[0] + invMat[4] * vNewWorld[1] + invMat[8] *  vNewWorld[2];
			vLocal[1] = invMat[1] * vNewWorld[0] + invMat[5] * vNewWorld[1] + invMat[9] *  vNewWorld[2];
			vLocal[2] = invMat[2] * vNewWorld[0] + invMat[6] * vNewWorld[1] + invMat[10] * vNewWorld[2];
            }

        /////////////////////////////////////////////////////////////////////////////
        // Transform a point by frame matrix
        void TransformPoint(M3DVector3f vPointSrc, M3DVector3f vPointDst)
            {
            M3DMatrix44f m;
            GetMatrix(m, false);    // Rotate and translate
            vPointDst[0] = m[0] * vPointSrc[0] + m[4] * vPointSrc[1] + m[8] *  vPointSrc[2] + m[12];// * v[3];
            vPointDst[1] = m[1] * vPointSrc[0] + m[5] * vPointSrc[1] + m[9] *  vPointSrc[2] + m[13];// * v[3];
            vPointDst[2] = m[2] * vPointSrc[0] + m[6] * vPointSrc[1] + m[10] * vPointSrc[2] + m[14];// * v[3];
            }

        ////////////////////////////////////////////////////////////////////////////
        // Rotate a vector by frame matrix
        void RotateVector(M3DVector3f vVectorSrc, M3DVector3f vVectorDst)
            {
            M3DMatrix44f m;
            GetMatrix(m, true);    // Rotate only

            vVectorDst[0] = m[0] * vVectorSrc[0] + m[4] * vVectorSrc[1] + m[8] *  vVectorSrc[2];
            vVectorDst[1] = m[1] * vVectorSrc[0] + m[5] * vVectorSrc[1] + m[9] *  vVectorSrc[2];
            vVectorDst[2] = m[2] * vVectorSrc[0] + m[6] * vVectorSrc[1] + m[10] * vVectorSrc[2];
            }
    };

/**
 *Code Part
 */

#define NUM_SPHERES      30
GLFrame    spheres[NUM_SPHERES];
GLFrame    frameCamera;

// Light and material Data
GLfloat fLightPos[4]   = { -100.0f, 100.0f, 50.0f, 1.0f };  // Point source
GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat fLowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat fBrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

M3DMatrix44f mShadowMatrix;

#define GROUND_TEXTURE  0
#define TORUS_TEXTURE   1
#define SPHERE_TEXTURE  2
#define NUM_TEXTURES    3
GLuint  textureObjects[NUM_TEXTURES];

const char *szTextureFiles[] = {"../grass.tga", "../wood.tga", "../orb.tga"};

        
//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
    M3DVector3f vPoints[3] = {{ 0.0f, -0.4f, 0.0f },
                             { 10.0f, -0.4f, 0.0f },
                             { 5.0f, -0.4f, -5.0f }};
    int iSphere;
    int i;
    
    // Grayish background
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);
   
    // Clear stencil buffer with zero, increment by one whenever anybody
    // draws into it. When stencil function is enabled, only write where
    // stencil value is zero. This prevents the transparent shadow from drawing
    // over itself
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);
    glClearStencil(0);
    glStencilFunc(GL_EQUAL, 0x0, 0x01);
    
    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);
    
    // Setup light parameters
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fNoLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, fLowLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, fBrightLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
        
    // Calculate shadow matrix
    M3DVector4f pPlane;
    m3dGetPlaneEquation(pPlane, vPoints[0], vPoints[1], vPoints[2]);
    m3dMakePlanarShadowMatrix(mShadowMatrix, pPlane, fLightPos);
    
    // Mostly use material tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fBrightLight);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
  
    
    // Randomly place the sphere inhabitants
    for(iSphere = 0; iSphere < NUM_SPHERES; iSphere++)
        {
        // Pick a random location between -20 and 20 at .1 increments
        spheres[iSphere].SetOrigin(((float)((rand() % 400) - 200) * 0.1f), 0.0, (float)((rand() % 400) - 200) * 0.1f);
        }
      
    // Set up texture maps
    glEnable(GL_TEXTURE_2D);
    glGenTextures(NUM_TEXTURES, textureObjects);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    for(i = 0; i < NUM_TEXTURES; i++)
        {
        GLbyte *pBytes;
        GLint iWidth, iHeight, iComponents;
        GLenum eFormat;
        
        glBindTexture(GL_TEXTURE_2D, textureObjects[i]);
        
        // Load this texture map
        pBytes = gltLoadTGA(szTextureFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);
        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight,
        	eFormat, GL_UNSIGNED_BYTE, pBytes);
        free(pBytes);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

    }

////////////////////////////////////////////////////////////////////////
// Do shutdown for the rendering context
void ShutdownRC(void)
    {
    // Delete the textures
    glDeleteTextures(NUM_TEXTURES, textureObjects);
    }


///////////////////////////////////////////////////////////
// Draw the ground as a series of triangle strips
void DrawGround(void)
    {
    GLfloat fExtent = 20.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = -0.4f;
    GLfloat iStrip, iRun;
    GLfloat s = 0.0f;
    GLfloat t = 0.0f;
    GLfloat texStep = 1.0f / (fExtent * .075f);
    
    glBindTexture(GL_TEXTURE_2D, textureObjects[GROUND_TEXTURE]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    for(iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep)
        {
        t = 0.0f;
        glBegin(GL_TRIANGLE_STRIP);

            for(iRun = fExtent; iRun >= -fExtent; iRun -= fStep)
                {
                glTexCoord2f(s, t);
                glNormal3f(0.0f, 1.0f, 0.0f);   // All Point up
                glVertex3f(iStrip, y, iRun);
                
                glTexCoord2f(s + texStep, t);
                glNormal3f(0.0f, 1.0f, 0.0f);   // All Point up
                glVertex3f(iStrip + fStep, y, iRun);
                
                t += texStep;
                }
        glEnd();
        s += texStep;
        }
    }

///////////////////////////////////////////////////////////////////////
// Draw random inhabitants and the rotating torus/sphere duo
void DrawInhabitants(GLint nShadow)
    {
    static GLfloat yRot = 0.0f;         // Rotation angle for animation
    GLint i;

    if(nShadow == 0){
        yRot += 0.5f;
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
        glColor4f(0.00f, 0.00f, 0.00f, .6f);  // Shadow color
  
        
    // Draw the randomly located spheres
    glBindTexture(GL_TEXTURE_2D, textureObjects[SPHERE_TEXTURE]);
    for(i = 0; i < NUM_SPHERES; i++){
        glPushMatrix();
        spheres[i].ApplyActorTransform();
        gltDrawSphere(0.3f, 21, 11);
        glPopMatrix();
    }
	//***/
    glPushMatrix();
        glTranslatef(0.0f, 0.1f, -2.5f);
    
        glPushMatrix();
            glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
            glTranslatef(1.0f, 0.0f, 0.0f);
            gltDrawSphere(0.1f,21, 11);
        glPopMatrix();
    
        if(nShadow == 0){
            // Torus alone will be specular
            glMaterialfv(GL_FRONT, GL_SPECULAR, fBrightLight);
        }
        
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, textureObjects[TORUS_TEXTURE]);
        gltDrawTorus(0.35, 0.15, 61, 37);
        glMaterialfv(GL_FRONT, GL_SPECULAR, fNoLight);
    glPopMatrix();
    }

        
// Called to draw scene
void RenderScene(void)
    {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
    glPushMatrix();
        frameCamera.ApplyCameraTransform();
        
        // Position light before any other transformations
        glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
        
        // Draw the ground
        glColor3f(1.0f, 1.0f, 1.0f);
        DrawGround();
        
        // Draw shadows first
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_STENCIL_TEST);
        glPushMatrix();
            glMultMatrixf(mShadowMatrix);
            DrawInhabitants(1);
        glPopMatrix();
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        
        // Draw inhabitants normally
        DrawInhabitants(0);

    glPopMatrix();
        
    // Do the buffer Swap
    glutSwapBuffers();
    }



// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
    {
    if(key == GLUT_KEY_UP)
        frameCamera.MoveForward(0.1f);

    if(key == GLUT_KEY_DOWN)
		frameCamera.MoveForward(-0.1f);

    if(key == GLUT_KEY_LEFT)
		frameCamera.RotateLocalY(0.1f);
	   
    if(key == GLUT_KEY_RIGHT)
        frameCamera.RotateLocalY(-0.1f);
                        
    // Refresh the Window
    glutPostRedisplay();
    }

///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
    {
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(3,TimerFunction, 1);
    }

void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
        
    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    // Set the clipping volume
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
    }

int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL SphereWorld Demo + Texture Maps");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

    SetupRC();
    glutTimerFunc(33, TimerFunction, 1);

    glutMainLoop();
    
    ShutdownRC();

    return 0;
    }
