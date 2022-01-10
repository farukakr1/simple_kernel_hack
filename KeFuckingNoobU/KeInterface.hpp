/* Cheat that uses a driver for reading / writing virtual memory,
instead of using Win32API Functions. Written By Zer0Mem0ry,
https://www.youtube.com/watch?v=sJdBtPosWQs */

#include <Windows.h>

/* IOCTL Codes needed for our driver */

// Request to read virtual user memory (memory of a program) from kernel space
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to write virtual user memory (memory of a program) from kernel space
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the process id of client process, from kernel space
#define IO_GET_ID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0703 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


// datatype for read request
typedef struct _KERNEL_READ_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	PVOID pBuff;
	ULONG Size;

} KERNEL_READ_REQUEST, * PKERNEL_READ_REQUEST;

typedef struct _KERNEL_WRITE_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	PVOID pBuff;
	ULONG Size;

} KERNEL_WRITE_REQUEST, * PKERNEL_WRITE_REQUEST;

typedef struct _KERNEL_GET_ID_REQUEST
{
	const char* ClientName;
	ULONG* pBuff;
} KERNEL_GET_ID_REQUEST, * PKERNEL_GET_ID_REQUEST;


// interface for our driver
class KeInterface
{
public:
	HANDLE hDriver; // Handle to driver

					// Initializer
	KeInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	template <typename type>
	type ReadVirtualMemory(ULONG ProcessId, ULONG ReadAddress, SIZE_T Size)
	{
		// allocate a buffer with specified type to allow our driver to write our wanted data inside this buffer
		type Buffer;

		DWORD Return, Bytes;
		KERNEL_READ_REQUEST ReadRequest;


		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address = ReadAddress;

		//send the 'address' of the buffer so our driver can know where to write the data
		ReadRequest.pBuff = &Buffer;

		ReadRequest.Size = Size;

		// send code to our driver with the arguments
		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0))
		{
			//return our buffer
			return Buffer;
		}
		return Buffer;
	}

	template <typename type>
	bool WriteVirtualMemory(ULONG ProcessId, ULONG WriteAddress, type WriteValue, SIZE_T WriteSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		KERNEL_WRITE_REQUEST  WriteRequest;
		WriteRequest.ProcessId = ProcessId;
		WriteRequest.Address = WriteAddress;

		//send driver the 'address' of our specified type WriteValue so our driver can copy the data we want to write from this address to WriteAddress
		WriteRequest.pBuff = &WriteValue;

		WriteRequest.Size = WriteSize;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest), 0, 0, &Bytes, NULL))
		{
			return true;
		}
		return false;
	}

	DWORD GetTargetPid(const char* ClientName)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;

		DWORD Buffer;

		DWORD Return, Bytes;
		KERNEL_GET_ID_REQUEST  GetIDReq;
		GetIDReq.ClientName = ClientName;

		std::cout << GetIDReq.ClientName << std::endl;

		//send the 'address' of the buffer so our driver can know where to write the data
		GetIDReq.pBuff = &Buffer;

		// send code to our driver with the arguments
		if (DeviceIoControl(hDriver, IO_GET_ID_REQUEST, &GetIDReq, sizeof(GetIDReq), &GetIDReq, sizeof(GetIDReq), 0, 0))
		{
			//return our buffer
			return Buffer;
		}
		return Buffer;
	}
};