# Frozen FinsROV protocol

Imported without interface changes from NXTelemetryMonitor commit `5ebe00e2573c8df5b5ad376915fab2da0644c188`. [provenance.json](provenance.json) records SHA-256 for XML, generated C headers, Python dialect and common test vectors. `.gitattributes` disables newline conversion for these exact-byte imports.

Do not independently renumber fields/messages or regenerate against another XML. Existing generator notices remain. The source checkout had no root LICENSE; provenance does not grant a new license or supersede existing notices. Confirm redistribution permission before public release.

The bridge translates sessions and source timestamps on the MCU link, preserving validity. See the [integration contract](../docs/software/pc-nx-mcu.zh-CN.md).
