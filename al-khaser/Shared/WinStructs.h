#pragma once

typedef struct _LDR_MODULE {
	LIST_ENTRY              InLoadOrderModuleList;
	LIST_ENTRY              InMemoryOrderModuleList;
	LIST_ENTRY              InInitializationOrderModuleList;
	PVOID                   BaseAddress;
	PVOID                   EntryPoint;
	ULONG                   SizeOfImage;
	UNICODE_STRING          FullDllName;
	UNICODE_STRING          BaseDllName;
	ULONG                   Flags;
	SHORT                   LoadCount;
	SHORT                   TlsIndex;
	LIST_ENTRY              HashTableEntry;
	ULONG                   TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef LONG KPRIORITY;

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _PEB64 {
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID64 Reserved3[2];
	PVOID64 Ldr;
	PVOID64 ProcessParameters;
	BYTE Reserved4[104];
	PVOID64 Reserved5[52];
	PVOID64 PostProcessInitRoutine;
	BYTE Reserved6[128];
	PVOID64 Reserved7[1];
	ULONG SessionId;
} PEB64, *PPEB64;

typedef struct _PEB_LDR_DATA64 {
	BYTE Reserved1[8];
	PVOID64 Reserved2[3];
	LIST_ENTRY64 InMemoryOrderModuleList;
} PEB_LDR_DATA64, *PPEB_LDR_DATA64;

typedef struct _UNICODE_STRING64 {
	USHORT Length;
	USHORT MaximumLength;
	PVOID64  Buffer;
} UNICODE_STRING64;

typedef struct _LDR_DATA_TABLE_ENTRY64 {
	PVOID64 Reserved1[2];
	LIST_ENTRY64 InMemoryOrderLinks;
	PVOID64 Reserved2[2];
	PVOID64 DllBase;
	PVOID64 Reserved3[2];
	UNICODE_STRING64 FullDllName;
	BYTE Reserved4[8];
	PVOID64 Reserved5[3];
	union {
		ULONG CheckSum;
		PVOID64 Reserved6;
	} DUMMYUNIONNAME;
	ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

/*++ NtCreateThreadEx specific */

typedef struct _PS_ATTRIBUTE {
	ULONG Attribute;
	SIZE_T Size;
	union
	{
		ULONG Value;
		PVOID ValuePtr;
	} u1;
	PSIZE_T ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST {
	SIZE_T TotalLength;
	PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

#define PS_ATTRIBUTE_NUMBER_MASK 0x0000ffff
#define PS_ATTRIBUTE_THREAD 0x00010000
#define PS_ATTRIBUTE_INPUT 0x00020000
#define PS_ATTRIBUTE_ADDITIVE 0x00040000

#define PsAttributeValue(Number, Thread, Input, Additive) \
	(((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
	((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
	((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
	((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

typedef enum _PS_ATTRIBUTE_NUM {
	PsAttributeClientId = 3,
} PS_ATTRIBUTE_NUM;

#define PS_ATTRIBUTE_CLIENT_ID \
    PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE)

/* NtCreateThreadEx specific --*/


typedef VOID(NTAPI LDR_ENUM_CALLBACK)(_In_ PLDR_DATA_TABLE_ENTRY ModuleInformation, _In_ PVOID Parameter, _Out_ BOOLEAN *Stop);
typedef LDR_ENUM_CALLBACK *PLDR_ENUM_CALLBACK;

typedef struct _IDENTIFY_DEVICE_DATA {
	struct {
		USHORT Reserved1 : 1;
		USHORT Retired3 : 1;
		USHORT ResponseIncomplete : 1;
		USHORT Retired2 : 3;
		USHORT FixedDevice : 1;
		USHORT RemovableMedia : 1;
		USHORT Retired1 : 7;
		USHORT DeviceType : 1;
	} GeneralConfiguration;
	USHORT NumCylinders;
	USHORT ReservedWord2;
	USHORT NumHeads;
	USHORT Retired1[2];
	USHORT NumSectorsPerTrack;
	USHORT VendorUnique1[3];
	UCHAR  SerialNumber[20];
	USHORT Retired2[2];
	USHORT Obsolete1;
	UCHAR  FirmwareRevision[8];
	UCHAR  ModelNumber[40];
	UCHAR  MaximumBlockTransfer;
	UCHAR  VendorUnique2;
	USHORT ReservedWord48;
	struct {
		UCHAR  ReservedByte49;
		UCHAR  DmaSupported : 1;
		UCHAR  LbaSupported : 1;
		UCHAR  IordyDisable : 1;
		UCHAR  IordySupported : 1;
		UCHAR  Reserved1 : 1;
		UCHAR  StandybyTimerSupport : 1;
		UCHAR  Reserved2 : 2;
		USHORT ReservedWord50;
	} Capabilities;
	USHORT ObsoleteWords51[2];
	USHORT TranslationFieldsValid : 3;
	USHORT Reserved3 : 13;
	USHORT NumberOfCurrentCylinders;
	USHORT NumberOfCurrentHeads;
	USHORT CurrentSectorsPerTrack;
	ULONG  CurrentSectorCapacity;
	UCHAR  CurrentMultiSectorSetting;
	UCHAR  MultiSectorSettingValid : 1;
	UCHAR  ReservedByte59 : 7;
	ULONG  UserAddressableSectors;
	USHORT ObsoleteWord62;
	USHORT MultiWordDMASupport : 8;
	USHORT MultiWordDMAActive : 8;
	USHORT AdvancedPIOModes : 8;
	USHORT ReservedByte64 : 8;
	USHORT MinimumMWXferCycleTime;
	USHORT RecommendedMWXferCycleTime;
	USHORT MinimumPIOCycleTime;
	USHORT MinimumPIOCycleTimeIORDY;
	USHORT ReservedWords69[6];
	USHORT QueueDepth : 5;
	USHORT ReservedWord75 : 11;
	USHORT ReservedWords76[4];
	USHORT MajorRevision;
	USHORT MinorRevision;
	struct {
		USHORT SmartCommands : 1;
		USHORT SecurityMode : 1;
		USHORT RemovableMediaFeature : 1;
		USHORT PowerManagement : 1;
		USHORT Reserved1 : 1;
		USHORT WriteCache : 1;
		USHORT LookAhead : 1;
		USHORT ReleaseInterrupt : 1;
		USHORT ServiceInterrupt : 1;
		USHORT DeviceReset : 1;
		USHORT HostProtectedArea : 1;
		USHORT Obsolete1 : 1;
		USHORT WriteBuffer : 1;
		USHORT ReadBuffer : 1;
		USHORT Nop : 1;
		USHORT Obsolete2 : 1;
		USHORT DownloadMicrocode : 1;
		USHORT DmaQueued : 1;
		USHORT Cfa : 1;
		USHORT AdvancedPm : 1;
		USHORT Msn : 1;
		USHORT PowerUpInStandby : 1;
		USHORT ManualPowerUp : 1;
		USHORT Reserved2 : 1;
		USHORT SetMax : 1;
		USHORT Acoustics : 1;
		USHORT BigLba : 1;
		USHORT DeviceConfigOverlay : 1;
		USHORT FlushCache : 1;
		USHORT FlushCacheExt : 1;
		USHORT Resrved3 : 2;
		USHORT SmartErrorLog : 1;
		USHORT SmartSelfTest : 1;
		USHORT MediaSerialNumber : 1;
		USHORT MediaCardPassThrough : 1;
		USHORT StreamingFeature : 1;
		USHORT GpLogging : 1;
		USHORT WriteFua : 1;
		USHORT WriteQueuedFua : 1;
		USHORT WWN64Bit : 1;
		USHORT URGReadStream : 1;
		USHORT URGWriteStream : 1;
		USHORT ReservedForTechReport : 2;
		USHORT IdleWithUnloadFeature : 1;
		USHORT Reserved4 : 2;
	} CommandSetSupport;
	struct {
		USHORT SmartCommands : 1;
		USHORT SecurityMode : 1;
		USHORT RemovableMediaFeature : 1;
		USHORT PowerManagement : 1;
		USHORT Reserved1 : 1;
		USHORT WriteCache : 1;
		USHORT LookAhead : 1;
		USHORT ReleaseInterrupt : 1;
		USHORT ServiceInterrupt : 1;
		USHORT DeviceReset : 1;
		USHORT HostProtectedArea : 1;
		USHORT Obsolete1 : 1;
		USHORT WriteBuffer : 1;
		USHORT ReadBuffer : 1;
		USHORT Nop : 1;
		USHORT Obsolete2 : 1;
		USHORT DownloadMicrocode : 1;
		USHORT DmaQueued : 1;
		USHORT Cfa : 1;
		USHORT AdvancedPm : 1;
		USHORT Msn : 1;
		USHORT PowerUpInStandby : 1;
		USHORT ManualPowerUp : 1;
		USHORT Reserved2 : 1;
		USHORT SetMax : 1;
		USHORT Acoustics : 1;
		USHORT BigLba : 1;
		USHORT DeviceConfigOverlay : 1;
		USHORT FlushCache : 1;
		USHORT FlushCacheExt : 1;
		USHORT Resrved3 : 2;
		USHORT SmartErrorLog : 1;
		USHORT SmartSelfTest : 1;
		USHORT MediaSerialNumber : 1;
		USHORT MediaCardPassThrough : 1;
		USHORT StreamingFeature : 1;
		USHORT GpLogging : 1;
		USHORT WriteFua : 1;
		USHORT WriteQueuedFua : 1;
		USHORT WWN64Bit : 1;
		USHORT URGReadStream : 1;
		USHORT URGWriteStream : 1;
		USHORT ReservedForTechReport : 2;
		USHORT IdleWithUnloadFeature : 1;
		USHORT Reserved4 : 2;
	} CommandSetActive;
	USHORT UltraDMASupport : 8;
	USHORT UltraDMAActive : 8;
	USHORT ReservedWord89[4];
	USHORT HardwareResetResult;
	USHORT CurrentAcousticValue : 8;
	USHORT RecommendedAcousticValue : 8;
	USHORT ReservedWord95[5];
	ULONG  Max48BitLBA[2];
	USHORT StreamingTransferTime;
	USHORT ReservedWord105;
	struct {
		USHORT LogicalSectorsPerPhysicalSector : 4;
		USHORT Reserved0 : 8;
		USHORT LogicalSectorLongerThan256Words : 1;
		USHORT MultipleLogicalSectorsPerPhysicalSector : 1;
		USHORT Reserved1 : 2;
	} PhysicalLogicalSectorSize;
	USHORT InterSeekDelay;
	USHORT WorldWideName[4];
	USHORT ReservedForWorldWideName128[4];
	USHORT ReservedForTlcTechnicalReport;
	USHORT WordsPerLogicalSector[2];
	struct {
		USHORT ReservedForDrqTechnicalReport : 1;
		USHORT WriteReadVerifySupported : 1;
		USHORT Reserved01 : 11;
		USHORT Reserved1 : 2;
	} CommandSetSupportExt;
	struct {
		USHORT ReservedForDrqTechnicalReport : 1;
		USHORT WriteReadVerifyEnabled : 1;
		USHORT Reserved01 : 11;
		USHORT Reserved1 : 2;
	} CommandSetActiveExt;
	USHORT ReservedForExpandedSupportandActive[6];
	USHORT MsnSupport : 2;
	USHORT ReservedWord1274 : 14;
	struct {
		USHORT SecuritySupported : 1;
		USHORT SecurityEnabled : 1;
		USHORT SecurityLocked : 1;
		USHORT SecurityFrozen : 1;
		USHORT SecurityCountExpired : 1;
		USHORT EnhancedSecurityEraseSupported : 1;
		USHORT Reserved0 : 2;
		USHORT SecurityLevel : 1;
		USHORT Reserved1 : 7;
	} SecurityStatus;
	USHORT ReservedWord129[31];
	struct {
		USHORT MaximumCurrentInMA2 : 12;
		USHORT CfaPowerMode1Disabled : 1;
		USHORT CfaPowerMode1Required : 1;
		USHORT Reserved0 : 1;
		USHORT Word160Supported : 1;
	} CfaPowerModel;
	USHORT ReservedForCfaWord161[8];
	struct {
		USHORT SupportsTrim : 1;
		USHORT Reserved0 : 15;
	} DataSetManagementFeature;
	USHORT ReservedForCfaWord170[6];
	USHORT CurrentMediaSerialNumber[30];
	USHORT ReservedWord206;
	USHORT ReservedWord207[2];
	struct {
		USHORT AlignmentOfLogicalWithinPhysical : 14;
		USHORT Word209Supported : 1;
		USHORT Reserved0 : 1;
	} BlockAlignment;
	USHORT WriteReadVerifySectorCountMode3Only[2];
	USHORT WriteReadVerifySectorCountMode2Only[2];
	struct {
		USHORT NVCachePowerModeEnabled : 1;
		USHORT Reserved0 : 3;
		USHORT NVCacheFeatureSetEnabled : 1;
		USHORT Reserved1 : 3;
		USHORT NVCachePowerModeVersion : 4;
		USHORT NVCacheFeatureSetVersion : 4;
	} NVCacheCapabilities;
	USHORT NVCacheSizeLSW;
	USHORT NVCacheSizeMSW;
	USHORT NominalMediaRotationRate;
	USHORT ReservedWord218;
	struct {
		UCHAR NVCacheEstimatedTimeToSpinUpInSeconds;
		UCHAR Reserved;
	} NVCacheOptions;
	USHORT ReservedWord220[35];
	USHORT Signature : 8;
	USHORT CheckSum : 8;
} IDENTIFY_DEVICE_DATA, *PIDENTIFY_DEVICE_DATA;
