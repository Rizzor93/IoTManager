/*=============================================================================|
|  PROJECT SimpleIoT                                                     1.0.0 |
|==============================================================================|
|  Copyright (C) 2021, Christoph Bortolot                                      |
|  All rights reserved.                                                        |
|=============================================================================*/
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <vector>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVariantList>
#include <QStringListModel>
#include <QAbstractListModel>
#include <QQmlListProperty>
#include <QDateTime>

namespace util {
    namespace conversion {
        // LOCAL-Time
        inline std::string currentDateTimeStringLocalTime() {
            time_t now = time(nullptr);
            struct tm tstruct{};
            char stringDateTime[80];
            tstruct = *localtime(&now);
            strftime(stringDateTime, sizeof(stringDateTime), "%Y-%m-%d %H:%M:%S %z", &tstruct);
            return stringDateTime;
        }

        inline long stringDateTimeToSecondsLocalTime(const std::string &time_details) {
            struct tm tm{};

            strptime(time_details.c_str(), "%Y-%m-%d %H:%M:%S %z", &tm);
            time_t t = mktime(&tm);
            return t;
        }

        inline std::string secondsDateTimeToStringLocalTime(const long &secSinceEpoch) {
            time_t now = secSinceEpoch;
            struct tm tstruct{};
            char stringDateTime[80];
            tstruct = *localtime(&now);
            strftime(stringDateTime, sizeof(stringDateTime), "%d-%m-%Y %H:%M:%S", &tstruct);
            return stringDateTime;
        }

        // UTC-Time
        inline long currentDateTimeUnixEpoch() {
            time_t rawtime{};
            time(&rawtime);
            return rawtime;
        }

        inline std::string currentDateTimeStringUTC() {
            time_t rawtime;
            struct tm *ptm;
            char stringDateTime[80];
            time(&rawtime);
            ptm = gmtime(&rawtime);
            strftime(stringDateTime, sizeof(stringDateTime), "%d-%m-%Y %H:%M:%S", ptm);
            return stringDateTime;
        }

        inline double stringDateTimeToSecondsUTC(const std::string &time_details) {
            struct tm ptm{};
            time_t t;
            strptime(time_details.c_str(), "%d-%m-%Y %H:%M:%S", &ptm);

            t = timegm(&ptm);
            return t;
        }

        inline std::string secondsDateTimeToStringUTC(const double &secSinceEpoch) {
            time_t now = secSinceEpoch;
            struct tm tstruct{};
            char stringDateTime[100];
            tstruct = *gmtime(&now);
            strftime(stringDateTime, sizeof(stringDateTime), "%d-%m-%Y %H:%M:%S", &tstruct);
            return stringDateTime;
        }

        // HexString to double
        inline double hexStringToDouble(const QString &value) {
            double res;
            std::stringstream ss;
            ss << std::hex << value.toStdString();
            ss >> res;
            return res;
        }

        // Double to HexString
        inline std::string doubleToHex(const double &value) {
            std::stringstream ss;
            ss << std::hex << static_cast<int>(value);
            return ss.str();
        }

        // Bool to String
        inline const char *boolToString(bool b) {
            return b ? "true" : "false";
        }

        // QString to double
        inline double qStringToDouble(const QString &value) {
            return value.toDouble();
        }
    }
    namespace validation {
        /* Time-Validation
         * if given dateTime-String valid.
         * return = true.
         * DateTimeFormat = "dd-MM-yyyy hh:mm:ss".
         */
        inline bool timeValidation(const QString &dateTime) {
            QString dateTimeFormat = "dd-MM-yyyy hh:mm:ss";
            QDateTime time = QDateTime::fromString(dateTime, dateTimeFormat);
            return time.isValid();
        }

        /* Time-Compare
         * CompareMode = [<,>,==,>=,<=].
         * lValue = on the left side.
         * rValue = on the right side.
         * DateTimeFormat = "dd-MM-yyyy hh:mm:ss".
         */
        inline bool timeCompValidation(const QString &lValue, const QString &compareMode, const QString &rValue) {
            QString dateTimeFormat = "dd-MM-yyyy hh:mm:ss";
            QDateTime minTime = QDateTime::fromString(lValue, dateTimeFormat);
            QDateTime maxTime = QDateTime::fromString(rValue, dateTimeFormat);

            if (compareMode == ">")
                return minTime.operator>(maxTime);
            if (compareMode == "<")
                return minTime.operator<(maxTime);
            if (compareMode == "<=")
                return minTime.operator<=(maxTime);
            if (compareMode == ">=")
                return minTime.operator>=(maxTime);
            if (compareMode == "==")
                return minTime.operator==(maxTime);
            else
                return false;
        }

        /* Decimal-Compare
         * CompareMode = [<,>,==,>=,<=].
         * lValue = on the left side.
         * rValue = on the right side.
         */
        inline bool decimalCompValidation(const double &lValue, const QString &compareMode, const double &rValue) {
            if (compareMode == ">")
                return lValue > rValue;
            if (compareMode == "<")
                return lValue < rValue;
            if (compareMode == "<=")
                return lValue <= rValue;
            if (compareMode == ">=")
                return lValue >= rValue;
            if (compareMode == "==")
                return lValue == rValue;
            else
                return false;
        }

        /* Hex-Compare
         * Hex will convert in double
         * CompareMode = [<,>,==,>=,<=].
         * lValue = on the left side.
         * rValue = on the right side.
         */
        inline bool hexCompValidation(const QString &lValue, const QString &compareMode, const QString &rValue) {
            if (compareMode == ">")
                return conversion::hexStringToDouble(lValue) > conversion::hexStringToDouble(rValue);
            if (compareMode == "<")
                return conversion::hexStringToDouble(lValue) < conversion::hexStringToDouble(rValue);
            if (compareMode == "<=")
                return conversion::hexStringToDouble(lValue) <= conversion::hexStringToDouble(rValue);
            if (compareMode == ">=")
                return conversion::hexStringToDouble(lValue) >= conversion::hexStringToDouble(rValue);
            if (compareMode == "==")
                return conversion::hexStringToDouble(lValue) == conversion::hexStringToDouble(rValue);
            else
                return false;
        }

        /* Hex-Validation
         * Check if Hex-String valid
         * return true
         */
        inline bool hexValidation(const QString &value) {
            float res;
            std::stringstream ss;
            ss << std::hex << value.toStdString();
            ss >> res;
            return !ss.fail();
        }
    }
    namespace types {
        // Device
        Q_NAMESPACE
        enum class DeviceType {
            ARDUINO,
            RASPBERRYPI,
            PLC_Siemens,
            PLC_Beckhoff,
            PLC_WAGO,
            OPC
        };

        Q_ENUM_NS(DeviceType)

        struct Device {
            int ID{};
            QString Name{};
            QString Location{};
            DeviceType DeviceType{};
            QString OPCUrl{};
            QString IPAddress{};
            QString Gateway{};
            QString SubnetMask{};

            inline bool operator==(Device const &other) const {
                // compare members
                if (this->ID != other.ID)
                    return false;
                if (this->Name != other.Name)
                    return false;
                if (this->Location != other.Location)
                    return false;
                if (this->DeviceType != other.DeviceType)
                    return false;
                if (this->OPCUrl != other.OPCUrl)
                    return false;
                if (this->IPAddress != other.IPAddress)
                    return false;
                if (this->SubnetMask != other.SubnetMask)
                    return false;
                if (this->Gateway != other.Gateway)
                    return false;

                return true;

            };

            inline bool operator!=(Device const &other) const {
                return !(*this == other);
            };

        };

        // Sensor
        enum class SensorDataType {
            BOOL,
            BYTE,
            INT,
            FLOAT,
            DOUBLE,
            STRING,
            DATETIME
        };

        Q_ENUM_NS(SensorDataType)

        enum class GPIOType {
            Input,
            Output,
            AnalogInput,
            AnalogOutput
        };

        Q_ENUM_NS(GPIOType)

        enum class PLCDataArea {
            DB,
            MK,
            PE,
            PA,
            CT
        };

        Q_ENUM_NS(PLCDataArea)

        struct Sensor {
            int ID{};
            int DeviceID{};
            QString Name{};
            SensorDataType SensorDataType{};
            // GPIO
            int GPIONum{};
            GPIOType GPIOType{};
            bool PullUpResistor{};
            // PLC
            PLCDataArea PLCDataArea{};
            int DataOffset{};
            int BoolIndex{};
            int DbNum{};
            // OPC
            QString NodeID{};

            inline bool operator==(Sensor const &other) const {
                // compare members
                if (this->ID != other.ID)
                    return false;
                if (this->Name != other.Name)
                    return false;
                if (this->SensorDataType != other.SensorDataType)
                    return false;
                if (this->GPIONum != other.GPIONum)
                    return false;
                if (this->PullUpResistor != other.PullUpResistor)
                    return false;
                if (this->PLCDataArea != other.PLCDataArea)
                    return false;
                if (this->DataOffset != other.DataOffset)
                    return false;
                if (this->BoolIndex != other.BoolIndex)
                    return false;
                if (this->DbNum != other.DbNum)
                    return false;
                if (this->NodeID != other.NodeID)
                    return false;
                return true;

            };

            inline bool operator!=(Sensor const &other) const {
                return !(*this == other);
            };
        };


        // Record
        enum class RecordType {
            EQUAL,
            ODD,
            SMALLER_THEN,
            BIGGER_THEN,
            RANGE,
            ALWAYS
        };

        Q_ENUM_NS(RecordType)

        struct RecordSensor {
            int SensorID{};
            RecordType RecordType{};
            QString TriggerValueMin{};
            QString TriggerValueMax{};
            double Interval{};

            inline bool operator==(RecordSensor const &other) const {
                // compare members
                if (this->SensorID != other.SensorID)
                    return false;
                if (this->RecordType != other.RecordType)
                    return false;
                if (this->TriggerValueMin != other.TriggerValueMin)
                    return false;
                if (this->TriggerValueMax != other.TriggerValueMax)
                    return false;
                if (this->Interval != other.Interval)
                    return false;

                return true;
            };

            inline bool operator!=(RecordSensor const &other) const {
                return !(*this == other);
            };

        };

        struct Record {
            int ID{};
            int DeviceID{};
            QString Name{};
            bool Running{};
            QList<RecordSensor> RecordSensor{};

            inline bool operator==(Record const &other) const {
                // compare members
                if (this->ID != other.ID)
                    return false;
                if (this->DeviceID != other.DeviceID)
                    return false;
                if (this->Name != other.Name)
                    return false;
                if (this->Running != other.Running)
                    return false;
                if (this->RecordSensor != other.RecordSensor)
                    return false;
                return true;

            };

            inline bool operator!=(Record const &other) const {
                return !(*this == other);
            };
        };

        // RecordData
        enum class FilterTime {
            NOW,
            LAST_24H,
            LAST_WEEK,
            LAST_MONTH,
            LAST_3MONTH,
            LAST_6MONTH,
            LAST_YEAR,
            ALL
        };

        Q_ENUM_NS(FilterTime)

        enum FilterValue {
            EQUAL_VALUE,
            ODD_VALUE,
            SMALLER_THEN_VALUE,
            BIGGER_THEN_VALUE,
            RANGE_VALUE,
            ALL_VALUE
        };

        Q_ENUM_NS(FilterValue)

        struct RecordData {
            int ID{};
            int SensorID{};
            SensorDataType SensorDataType{};
            QString Value{};
            double Timestamp{};
        };

        struct RecordDataFilter {
            int ID{};
            int SensorID{};
            FilterValue FilterValue{};
            QString MinValue{};
            QString MaxValue{};
            FilterTime FilterTime{};
        };

    }
}

#endif //UTILS_H
