#ifndef PLYExport_h
#define PLYExport_h

#include "vtk-8.1\vtkIOPLYModule.h"
#include "vtk-8.1\vtkSmartPointer.h"
#include "vtk-8.1\vtkWriter.h"

#include <string>

class vtkDataSetAttributes;
class vtkPolyData;
class vtkScalarsToColors;
class vtkStringArray;

#define VTK_LITTLE_ENDIAN 0
#define VTK_BIG_ENDIAN    1

#define VTK_COLOR_MODE_DEFAULT 0
#define VTK_COLOR_MODE_UNIFORM_CELL_COLOR 1
#define VTK_COLOR_MODE_UNIFORM_POINT_COLOR 2
#define VTK_COLOR_MODE_UNIFORM_COLOR 3
#define VTK_COLOR_MODE_OFF 4

#define VTK_TEXTURECOORDS_UV 0
#define VTK_TEXTURECOORDS_TEXTUREUV 1

class PLYExport : public vtkWriter
{
public:
	static PLYExport *New();
	vtkTypeMacro(PLYExport, vtkWriter);

	vtkSetClampMacro(DataByteOrder, int, VTK_LITTLE_ENDIAN, VTK_BIG_ENDIAN);
	vtkGetMacro(DataByteOrder, int);
	void SetDataByteOrderToBigEndian()
	{
		this->SetDataByteOrder(VTK_BIG_ENDIAN);
	}
	void SetDataByteOrderToLittleEndian()
	{
		this->SetDataByteOrder(VTK_LITTLE_ENDIAN);
	}

	vtkSetMacro(ColorMode, int);
	vtkGetMacro(ColorMode, int);
	void SetColorModeToDefault()
	{
		this->SetColorMode(VTK_COLOR_MODE_DEFAULT);
	}
	void SetColorModeToUniformCellColor()
	{
		this->SetColorMode(VTK_COLOR_MODE_UNIFORM_CELL_COLOR);
	}
	void SetColorModeToUniformPointColor()
	{
		this->SetColorMode(VTK_COLOR_MODE_UNIFORM_POINT_COLOR);
	}
	void SetColorModeToUniformColor()
	{
		this->SetColorMode(VTK_COLOR_MODE_UNIFORM_COLOR);
	}
	void SetColorModeToOff()
	{
		this->SetColorMode(VTK_COLOR_MODE_OFF);
	}

	vtkSetStringMacro(ArrayName);
	vtkGetStringMacro(ArrayName);

	vtkSetClampMacro(Component, int, 0, VTK_INT_MAX);
	vtkGetMacro(Component, int);

	virtual void SetLookupTable(vtkScalarsToColors*);
	vtkGetObjectMacro(LookupTable, vtkScalarsToColors);

	vtkSetVector3Macro(Color, unsigned char);
	vtkGetVector3Macro(Color, unsigned char);

	vtkPolyData* GetInput();
	vtkPolyData* GetInput(int port);

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

	vtkSetClampMacro(FileType, int, VTK_ASCII, VTK_BINARY);
	vtkGetMacro(FileType, int);
	void SetFileTypeToASCII() { this->SetFileType(VTK_ASCII); };
	void SetFileTypeToBinary() { this->SetFileType(VTK_BINARY); };

	vtkSetClampMacro(TextureCoordinatesName, int, VTK_TEXTURECOORDS_UV, VTK_TEXTURECOORDS_TEXTUREUV);
	vtkGetMacro(TextureCoordinatesName, int);
	void SetTextureCoordinatesNameToUV()
	{
		this->SetTextureCoordinatesName(VTK_TEXTURECOORDS_UV);
	}
	void SetTextureCoordinatesNameToTextureUV()
	{
		this->SetTextureCoordinatesName(VTK_TEXTURECOORDS_TEXTUREUV);
	}

	void AddComment(const std::string &comment);

protected:
	PLYExport();
	~PLYExport() VTK_OVERRIDE;

	void WriteData() VTK_OVERRIDE;
	unsigned char *GetColors(vtkIdType num, vtkDataSetAttributes *dsa);
	const float *GetTextureCoordinates(vtkIdType num, vtkDataSetAttributes *dsa);

	int DataByteOrder;
	char *ArrayName;
	int Component;
	int ColorMode;
	vtkScalarsToColors *LookupTable;
	unsigned char Color[3];

	char* FileName;

	int FileType;
	int TextureCoordinatesName;

	vtkSmartPointer<vtkStringArray> HeaderComments;

	int FillInputPortInformation(int port, vtkInformation *info) VTK_OVERRIDE;

private:
	PLYExport(const PLYExport&) VTK_DELETE_FUNCTION;
	void operator=(const PLYExport&) VTK_DELETE_FUNCTION;
};

#endif

