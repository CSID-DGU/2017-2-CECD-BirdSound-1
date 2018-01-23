#ifndef PNGImport_h
#define PNGImport_h

#include "vtk-8.1\vtkIOImageModule.h"
#include "vtk-8.1\vtkImageReader2.h"

class PNGImport : public vtkImageReader2
{
public:
	static PNGImport *New();
	vtkTypeMacro(PNGImport, vtkImageReader2);

	int CanReadFile(const char* fname) VTK_OVERRIDE;

	const char* GetFileExtensions() VTK_OVERRIDE
	{
		return ".png";
	}

	const char* GetDescriptiveName() VTK_OVERRIDE
	{
		return "PNG";
	}

	void GetTextChunks(const char* key, int beginEndIndex[2]);
	const char* GetTextKey(int index);
	const char* GetTextValue(int index);
	size_t GetNumberOfTextChunks();

	vtkSetMacro(ReadSpacingFromFile, bool);
	vtkGetMacro(ReadSpacingFromFile, bool);
	vtkBooleanMacro(ReadSpacingFromFile, bool);
	//@}
protected:
	PNGImport();
	~PNGImport() VTK_OVERRIDE;

	void ExecuteInformation() VTK_OVERRIDE;
	void ExecuteDataWithInformation(vtkDataObject *out, vtkInformation *outInfo) VTK_OVERRIDE;
	template <class OT>
	void PNGImportUpdate(vtkImageData *data, OT *outPtr);
	template <class OT>
	void PNGImportUpdate2(
		OT *outPtr, int *outExt, vtkIdType *outInc, long pixSize);


private:
	PNGImport(const PNGImport&) VTK_DELETE_FUNCTION;
	void operator=(const PNGImport&) VTK_DELETE_FUNCTION;

	class vtkInternals;
	vtkInternals* Internals;
	bool ReadSpacingFromFile;
};
#endif
