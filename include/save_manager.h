#include "bn_sram.h"
#include "bn_string.h"

class SaveManager {
    public:
        SaveManager();
        bool save_exists() const;
        bool load_save();
        void write_save();
        void erase_save();

        struct SaveData {
            char name[8] = { 0 };
            uint8_t gender = 0;
            uint16_t id = 0;
            uint16_t hours = 0;
            uint8_t minutes = 0;
            uint8_t seconds = 0;
            uint8_t frames = 0;
            uint8_t options[3] = {0, 0, 0};
            uint32_t checksum = 0;
        };

        const SaveData& data() const {
            return _data;
        }

        SaveData& data() {
            return _data;
        }
    private:
        SaveData _data;
        uint32_t _calculate_checksum(const SaveData& d) const;
};