/*
 * bit7z - A C++ static library to interface with the 7-zip DLLs.
 * Copyright (c) 2014-2018  Riccardo Ostani - All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * Bit7z is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bit7z; if not, see https://www.gnu.org/licenses/.
 */

#ifndef BITARCHIVEINFO_HPP
#define BITARCHIVEINFO_HPP

#include <vector>

#include "../include/bitarchiveopener.hpp"
#include "../include/bitinputarchive.hpp"
#include "../include/bitarchiveitem.hpp"
#include "../include/bittypes.hpp"

struct IInArchive;
struct IOutArchive;
struct IArchiveExtractCallback;

namespace bit7z {
    using std::vector;

    /**
     * @brief The BitArchiveInfo class allows to retrieve metadata information of archives and their content.
     */
    class BitArchiveInfo : public BitArchiveOpener, public BitInputArchive {
        public:
            /**
             * @brief Constructs a BitArchiveInfo object, opening the input file.
             *
             * @param lib       the 7z library used.
             * @param in_file   the input archive file path.
             * @param format    the input archive format.
             */
            BitArchiveInfo( const Bit7zLibrary& lib,
                            const wstring& in_file,
                            const BitInFormat& format = BitFormat::Auto );


            BitArchiveInfo( const Bit7zLibrary& lib,
                            const vector< byte_t >& in_buffer,
                            const BitInFormat& format = BitFormat::Auto );

            /**
             * @brief BitArchiveInfo destructor.
             *
             * @note It releases the input archive file.
             */
            virtual ~BitArchiveInfo() override;

            /**
             * @return a map of all the available (i.e. non empty) archive properties and their respective values.
             */
            map< BitProperty, BitPropVariant > archiveProperties() const;

            /**
             * @return a vector of all the archive items as BitArchiveItem objects.
             */
            vector< BitArchiveItem > items() const;

            /**
             * @return the number of folders contained in the archive.
             */
            uint32_t foldersCount() const;

            /**
             * @return the number of files contained in the archive.
             */
            uint32_t filesCount() const;

            /**
             * @return the total uncompressed size of the archive content.
             */
            uint64_t size() const;

            /**
             * @return the total compressed size of the archive content.
             */
            uint64_t packSize() const;

            bool hasEncryptedItems() const;

            uint32_t volumesCount() const;

            bool isMultiVolume() const;

            bool isSolid() const;
    };
}

#endif // BITARCHIVEINFO_HPP