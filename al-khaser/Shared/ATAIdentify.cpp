#include "pch.h"

/*
This function gets ATA IDENTIFY data for the first 16 PhysicalDrive objects and runs a check callback for each.
If any of the callbacks return true, this function returns true. Otherwise this function returns false.
See https://github.com/LordNoteworthy/al-khaser/issues/121 for more information.
*/
BOOL ata_identify_enum_with_callback(ata_identify_callback callback)
{
	// enumerate the first 16 drives. usually only one or two will exist.
	for (int driveNumber = 0; driveNumber < 16; driveNumber++)
	{
		char deviceNameBuffer[64] = { 0 };
		sprintf_s(deviceNameBuffer, "\\\\.\\PhysicalDrive%d", driveNumber);

		HANDLE diskHandle = CreateFileA(
			deviceNameBuffer,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			0,
			OPEN_EXISTING,
			0,
			0
		);

		if (diskHandle == INVALID_HANDLE_VALUE)
		{
			// failed to open handle
			continue;
		}

		// send an ATA IDENTIFY command
		const unsigned int IdentifyBufferSize = 512;
		const BYTE IdentifyCommandID = 0xEC;
		unsigned char Buffer[IdentifyBufferSize + sizeof(ATA_PASS_THROUGH_EX)] = { 0 };
		ATA_PASS_THROUGH_EX & pte = *reinterpret_cast<ATA_PASS_THROUGH_EX*>(Buffer);
		pte.Length = sizeof(pte);
		pte.TimeOutValue = 10;
		pte.DataTransferLength = 512;
		pte.DataBufferOffset = sizeof(ATA_PASS_THROUGH_EX);

		IDEREGS* regs = (IDEREGS*)pte.CurrentTaskFile;
		regs->bCommandReg = IdentifyCommandID;
		regs->bSectorCountReg = 1;

		pte.AtaFlags = ATA_FLAGS_DATA_IN | ATA_FLAGS_DRDY_REQUIRED;

		DWORD br = 0;
		BOOL ioctlSuccess = DeviceIoControl(
			diskHandle,
			IOCTL_ATA_PASS_THROUGH,
			&pte,
			sizeof(Buffer),
			&pte,
			sizeof(Buffer),
			&br,
			0
		);

		if (!ioctlSuccess)
		{
			// failed to get the IOCTL
			CloseHandle(diskHandle);
			continue;
		}

		IDENTIFY_DEVICE_DATA *idd = reinterpret_cast<IDENTIFY_DEVICE_DATA*>(Buffer + sizeof(ATA_PASS_THROUGH_EX));

		CloseHandle(diskHandle);

		if (callback(idd))
		{
			return TRUE;
		}
	}

	return FALSE;
}
