#pragma once
#include <ntifs.h>
#include <ntdef.h>

// Request to read virtual user memory (memory of a program) from kernel space
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to write virtual user memory (memory of a program) from kernel space
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the process id of client process, from kernel space
#define IO_GET_ID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0703 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the base address of client from kernel space
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0704 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to AllocateMemory user memory from kernel space
#define IO_ALLOC_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0705 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to change protection for user memory from kernel space
#define IO_VIRTUAL_PROTECT CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0706 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to free allocated user memory from kernel space
#define IO_FREE_MEMORY CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0707 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


PDEVICE_OBJECT pDeviceObject; // our driver object
UNICODE_STRING dev, dos; // Driver registry paths

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

typedef struct _KERNEL_ALLOC_REQUEST
{
	ULONG ProcessId;
	ULONG size;
	ULONG* pBuff;
} KERNEL_ALLOC_REQUEST, * PKERNEL_ALLOC_REQUEST;

typedef struct _KERNEL_VIRTUALPROTECT_REQUEST
{
	ULONG ProcessId;
	ULONG Address;
	ULONG size;
	ULONG Protect;
	ULONG* pBuff;
}KERNEL_VIRTUALPROTECT_REQUEST, * PKERNEL_VIRTUALPROTECT_REQUES;

typedef struct _KERNEL_FREEMEMORY_REQUEST
{
	ULONG ProcessId;
	ULONG Address;
	ULONG size;
}KERNEL_FREEMEMORY_REQUEST, * PKERNEL_FREEMEMORY_REQUEST;


NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP irp);
NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP irp);