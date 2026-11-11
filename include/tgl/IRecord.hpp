//
// Created by tete on 9/22/26.
//

#ifndef LIBTGL_IRECORD_HPP
#define LIBTGL_IRECORD_HPP

#include <cstdint>
#include <span>
#include <vector>
#include <tgl/typeUtilities.hpp>
#include <tgl/dynacast.hpp>

namespace tgl
{
    struct IRecord : IInterface
    {
        ~IRecord() override = default;
    protected:
        inline explicit IRecord(const std::span<const std::uint8_t>& bytes) { (void)bytes; }
        inline explicit IRecord() = default;

        [[nodiscard]] virtual std::vector<uint8_t> toBytes() const = 0;

        template<RealType From> requires std::is_base_of_v<IRecord, From>
        friend inline std::vector<uint8_t> checkedByteCast(const From& from)
        {
            return unsafe::uncheckedCast<IRecord>(from).toBytes();
        }

        template<RealType From> requires std::is_base_of_v<IRecord, From>
        friend inline std::vector<uint8_t> uncheckedByteCast(const From& from)
        {
            return unsafe::uncheckedCast<IRecord>(from).toBytes();
        }
    };
}

#endif //LIBTGL_IRECORD_HPP
