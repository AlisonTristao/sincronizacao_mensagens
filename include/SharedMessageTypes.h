#pragma once

#include <stdint.h>

// Keep this file synchronized across bally_software and t_dongle_develop.
enum class logType : uint8_t {
    NONE = 0,
    INFO,
    CMD,
    TELEMETRY,
    ERROR,
    DEBUG,
    PAKG,
    // Legacy aliases kept for compatibility with older naming.
    CMDO = CMD,
    TELE = TELEMETRY,
    ERRO = ERROR,
    DEBG = DEBUG
};

inline constexpr const char* logTypeToString(logType type) {
    switch (type) {
        case logType::INFO: return "INFO";
        case logType::CMD: return "CMD";
        case logType::TELEMETRY: return "TELEMETRY";
        case logType::ERROR: return "ERROR";
        case logType::DEBUG: return "DEBUG";
        case logType::PAKG: return "PAKG";
        case logType::NONE:
        default:
            return "NONE";
    }
};

// Packet metadata packed in one byte:
// bit 7     : last packet flag
// bits 0..6 : packet index (0..127)
static constexpr uint8_t MESSAGE_PACKET_LAST_FLAG = 0x80;
static constexpr uint8_t MESSAGE_PACKET_INDEX_MASK = 0x7F;
static constexpr uint8_t MESSAGE_PACKET_MAX_INDEX = 127;

inline constexpr uint8_t makePacketInfo(uint8_t packetIndex, bool isLastPacket) {
    return (packetIndex & MESSAGE_PACKET_INDEX_MASK) |
           (isLastPacket ? MESSAGE_PACKET_LAST_FLAG : 0);
}

inline constexpr uint8_t getPacketIndex(uint8_t packetInfo) {
    return packetInfo & MESSAGE_PACKET_INDEX_MASK;
}

inline constexpr bool isLastPacket(uint8_t packetInfo) {
    return (packetInfo & MESSAGE_PACKET_LAST_FLAG) != 0;
}
