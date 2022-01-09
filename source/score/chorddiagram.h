/*
 * Copyright (C) 2022 Cameron White
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCORE_CHORDDIAGRAM_H
#define SCORE_CHORDDIAGRAM_H

#include "chordname.h"
#include "fileversion.h"

class ChordDiagram
{
public:
    ChordDiagram();

    bool operator==(const ChordDiagram &other) const;

    template <class Archive>
    void serialize(Archive &ar, const FileVersion version);

    const ChordName &getChordName() const { return myChordName; }
    void setChordName(const ChordName &name) { myChordName = name; }

    int getTopFret() const { return myTopFret; }
    void setTopFret(int fret) { myTopFret = fret; }

    const std::vector<int> &getFretNumbers() const { return myFretNumbers; }
    void setFretNumbers(const std::vector<int> &frets) { myFretNumbers = frets; }

private:
    ChordName myChordName;
    int myTopFret = 0;
    /// Fret number for each string (not relative to the top fret)
    /// A negative number indicates a muted string.
    std::vector<int> myFretNumbers;
};

template <class Archive>
void ChordDiagram::serialize(Archive &ar, const FileVersion /*version*/)
{
    ar("chord_name", myChordName);
	ar("top_fret", myTopFret);
	ar("fret_numbers", myFretNumbers);
}

#endif
