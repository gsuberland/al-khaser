#pragma once

typedef BOOL(*ata_identify_callback)(IDENTIFY_DEVICE_DATA*);

BOOL ata_identify_enum_with_callback(ata_identify_callback callback);
