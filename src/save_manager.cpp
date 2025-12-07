#include "save_manager.h"

SaveManager::SaveManager() {}

bool SaveManager::save_exists() const {
    SaveManager::SaveData temp;
    bn::sram::read(temp);
    return temp.checksum == _calculate_checksum(temp);
}

void SaveManager::write_save() {
    _data.checksum = _calculate_checksum(_data);
    bn::sram::write(_data);
}

bool SaveManager::load_save() {
    SaveManager::SaveData temp;
    bn::sram::read(temp);

    if(temp.checksum != _calculate_checksum(temp)) {
        return false;
    }

    _data = temp;
    return true;
}

void SaveManager::erase_save() {
    bn::sram::clear(bn::sram::size());
}

uint32_t SaveManager::_calculate_checksum(const SaveData& d) const {
    SaveManager::SaveData copy = d;
    copy.checksum = 0;
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&copy);
    uint32_t sum = 0;

    for(std::size_t i = 0; i < sizeof(SaveManager::SaveData); i++) {
        sum += bytes[i];
    }

    return sum;
}