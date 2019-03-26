#include "DLMS_COSEM_objects.h"

const COSEM_OBJECT_Attribute attr_0_0_40_0_0_255[] = { // Объект текущего соединения (ОТС)
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_obj_list___2}, // 2 // Список объектов
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 3 // Идентификатор партнера
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 4 // Имя контекста приложения
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 5 // xDLMS_context_info
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 6 // Имя алгоритма проверки подлинности
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 7 // Секрет (пароль)
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 8 // Статус соединения
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_40_0_0_255___1}, // 9 // Ссылка на объект «Настройки безопасности»
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_0_0_40_0_0_255[] = { // Объект текущего соединения (ОТС)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_0_0_40_0_0_255___1}, // 1 // Ответ на проверку подлинности
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_0_0_40_0_0_255___1}, // 2 // Изменение пароля
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_0_0_40_0_0_255___1}, // 3 // Добавление объекта
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_0_0_40_0_0_255___1}, // 4 // Удаление объекта
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_0_0_42_0_0_255[] = { // Логическое имя устройства
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_dev_name___2}, // 2 // Имя устройства
    {0, 0, 0, (COA_rw)0} // end
};

//PDU_DataAccessResult attr_0_0_43_0_0_255___x(void *v_hdlc, void *v_pduHeader, COSEM_OBJECT *cobj, void *v_pduData); // Логическое имя объекта
//const COSEM_OBJECT_Attribute attr_0_0_43_0_0_255[] = { // Настройки безопасности
//    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name}, // 1 // Логическое имя объекта
//    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_43_0_0_255___x}, // 2 // Политика безопасности
//    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_43_0_0_255___x}, // 3 // Комплект безопасности
//    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_43_0_0_255___x}, // 4 // Название клиента
//    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_43_0_0_255___x}, // 5 // Название сервера
//    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_0_0_43_0_0_255___x}, // 6 // Сертификаты
//    {0, 0, 0, (COA_rw)0} // end
//};
//const COSEM_OBJECT_Attribute meth_0_0_43_0_0_255[] = { // Настройки безопасности
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 1 // Усиление безопасности (код)
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 2 // Передача ключа ()
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 3 // Ключевые соглашения
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 4 // Генерация пары для асимметричного ключа (тип)
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 5 // Запрос генерации сертификата (тип)
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 6 // Импорт сертификата (строка)
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 7 // Экспорт сертификата (структура)
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)0}, // 8 // Удаление сертификата (номер)
//    {0, 0, 0, (COA_rw)0} // end
//};

const COSEM_OBJECT_Attribute attr_clock[] = { // Часы
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 2 // time
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 3 // time_zone
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_clock___x}, // 4 // status
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 5 // daylight_savings_begin
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 6 // daylight_savings_end
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 7 // daylight_savings_deviation
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_clock___x}, // 8 // daylight_savings_enabled
    {DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_clock___x}, // 9 // clock_base
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_clock[] = { // Часы
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, (COA_rw)meth_clock___x}, // 1 // adjust_to_quarter (data)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, (COA_rw)meth_clock___x}, // 2 // adjust_to_measuring_period (data)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, (COA_rw)meth_clock___x}, // 3 // adjust_to_minute (data)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, (COA_rw)meth_clock___x}, // 4 // adjust_to_preset_time (data)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, (COA_rw)meth_clock___x}, // 5 // preset_adjusting_time (data)
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_clock___x}, // 6 // shift_time (data)
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_reg_value[] = { // мгновенные
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_value___2}, // 2 // Значение
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_value___3}, // 3 // Масштаб и ед. измерения
    {0, 0, 0, (COA_rw)0} // end
};
//const COSEM_OBJECT_Attribute meth_1_0_0_7_0_255[] = { // мгновенные
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)meth_0_0_1_0_0_255___1}, // 1 // Сброс
//    {0, 0, 0, (COA_rw)0} // end
//};

const COSEM_OBJECT_Attribute attr_reg_ext_value[] = { //
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_ext_value___x}, // 2 // Значение
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_ext_value___x}, // 3 // Масштаб и ед. измерения
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_ext_value___x}, // 4 // status CHOICE
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_ext_value___x}, // 5 // capture_time octet-string
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_reg_demand[] = { //
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 2 // Текущее среднее значение
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 3 // Последнее среднее значение
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 4 // Масштаб и ед. измерения
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 5 // Статус
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 6 // Время фиксации
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 7 // Время старта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_reg_demand___x}, // 8 // Длительность периода усреднения
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 9 // Количество периодов
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_reg_demand[] = { //
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 1 // Сброс
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_demand___x}, // 2 // Следующий период
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_profile_display[] = { // профиль
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_profile_display___x}, // 2 // buffer            // Буфер данных
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_profile_display___x}, // 3 // capture_objects   // Список отображаемых объектов
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_profile_display___x}, // 4 // capture_period    // Период пеключения экранов
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)0}, // 5 // sort_method       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)0}, // 6 // sort_object       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)0}, // 7 // entries_in_use    // Занятых записей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)0}, // 8 // profile_entries   // Всего записей
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_profile_0[] = { // профиль
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 2 // buffer            // Буфер данных
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 3 // capture_objects   // Список захватываемых объектов
//    {0, 0, 0, (COA_rw)0}, // end
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 4 // capture_period    // Период захвата
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 5 // sort_method       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 6 // sort_object       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 7 // entries_in_use    // Занятых записей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_0___x}, // 8 // profile_entries   // Всего записей
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_profile_0[] = { // профиль
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)attr_profile_0___x}, // 1 // Сброс
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)attr_profile_0___x}, // 2 // Захват
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_profile_event[] = { // профиль событий
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 2 // buffer            // Буфер данных
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 3 // capture_objects   // Список захватываемых объектов
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 4 // capture_period    // Период захвата
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 5 // sort_method       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 6 // sort_object       // Метод сортировки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 7 // entries_in_use    // Занятых записей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_profile_event___x}, // 8 // profile_entries   // Всего записей
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_profile_event[] = { // профиль событий
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)attr_profile_event___x}, // 1 // Сброс
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_passport[] = { // паспорт
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_passport_data}, // 2 // Буфер данных
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute attr_passport_rw[] = { // паспорт
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_passport_data}, // 2 // Буфер данных
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_event[] = { // паспорт
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_event_data___x}, // 2 // Буфер данных
    {0, 0, 0, (COA_rw)0} // end
};
#define meth_event 0
//const COSEM_OBJECT_Attribute meth_event[] = { // паспорт
//    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)attr_event_data___x}, // 1 // Сброс
//    {0, 0, 0, (COA_rw)0} // end
//};

const COSEM_OBJECT_Attribute attr_rs[] = { // RS
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_rs___x}, // 2 // Скорость обмена
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 3 // Размер окна передачи
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 4 // Размер окна приема
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 5 // Максимальная длина поля данных при передаче
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 6 // Максимальная длина поля данных при приеме
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 7 // Межсимвольный таймаут
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_rs___x}, // 8 // Межкадровый таймаут
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_rs___x}, // 9 // Адрес устройства
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_register_rw[] = { // настройки
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_register_rw___x}, // 2 // Значение
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_register_rw___x}, // 3 // Масштаб и ед. измерения
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_tariff[] = { // tariff
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
//    {0, 0, 0, (COA_rw)0}, // end
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 2 // Имя активного календаря
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 3 // Таблица активных сезонных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 4 // Таблица активных недельных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 5 // Таблица активных суточных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 6 // Имя пассивного календаря
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 7 // Таблица пассивных сезонных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 8 // Таблица пассивных недельных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 9 // Таблица пассивных суточных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_tariff___x}, // 10// Дата активирования пассивного календаря
    {0, 0, 0, (COA_rw)0} // end
};
const COSEM_OBJECT_Attribute meth_tariff[] = { // tariff
    {DLMS_METHOD_ACCESS_MODE_NONE, DLMS_METHOD_ACCESS_MODE_ACCESS, DLMS_METHOD_ACCESS_MODE_ACCESS, (COA_rw)attr_tariff___x}, // 1 // Активировать пассивный календарь ()
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_limit[] = { //
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_limit___x}, // 2 // Контролируемая величина
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_limit___x}, // 3 // Активный порог
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_limit___x}, // 4 // Нормальный порог
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_limit___x}, // 5 // Аварийный порог
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_limit___x}, // 6 // Мин. длительность превышения порога
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_limit___x}, // 7 // Мин. длительность снижения ниже порога
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_limit___x}, // 8 // Аварийный профиль
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_limit___x}, // 9 // Список аварийных профилей
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, (COA_rw)attr_limit___x}, // 10// Активный аварийный профиль
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_limit___x}, // 11// Действия
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_img_transf[] = { // Image Transfer
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 2 // Размер блока данных  06, 32-р. без знака
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 3 // Статус передачи блоков данных 04, строка битов
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 4 // Номер первого непереданного блока 06, 32-р. без знака
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 5 // Разрешение передачи данных 03, логическая
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 6 // Статус блока данных 22, из списка
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)attr_img_transf___x}, // 7 // Информация для активации 01, массив
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute meth_img_transf[] = { // Image Transfer
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)meth_img_transf___x}, // 1 // Инициализация передачи
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)meth_img_transf___x}, // 2 // Передача блока данных
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)meth_img_transf___x}, // 3 // Проверка файла
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, (COA_rw)meth_img_transf___x}, // 4 // Активирование файла
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT_Attribute attr_script[] = { // script
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_script___x}, // 2 // Сценарии
    {0, 0, 0, (COA_rw)0}, // end
};
const COSEM_OBJECT_Attribute meth_script[] = { // script
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_script___x}, // 1 // Выполнить (номер)
    {0, 0, 0, (COA_rw)0}, // end
};

const COSEM_OBJECT_Attribute attr_spec_days[] = { // spec_days
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_spec_days___x}, // 2 // массив дней
    {0, 0, 0, (COA_rw)0}, // end
};
//extern const COSEM_OBJECT_Attribute meth_spec_days[]; // spec_days

const COSEM_OBJECT_Attribute attr_reg_active[] = { // active
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_active___x}, // 2 // Назначенные регистры
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_active___x}, // 2 // Список масок
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_reg_active___x}, // 2 // Активная маска
    {0, 0, 0, (COA_rw)0}, // end
};
const COSEM_OBJECT_Attribute meth_reg_active[] = { // active
    {0, 0, 0, (COA_rw)0}, // end
};

const COSEM_OBJECT_Attribute attr_radio_bridge[] = { // radio
    {DLMS_ACCESS_MODE_NONE, DLMS_ACCESS_MODE_READ, DLMS_ACCESS_MODE_READ, (COA_rw)attr_logical_name___1}, // 1 // Логическое имя объекта
    {DLMS_ACCESS_MODE_READ_WRITE, DLMS_ACCESS_MODE_READ_WRITE, DLMS_ACCESS_MODE_READ_WRITE, (COA_rw)attr_radio_bridge_data}, // 2 // Буфер данных
    {0, 0, 0, (COA_rw)0} // end
};

const COSEM_OBJECT cosem_objcts_1_0_94_7_0_255[] = { // А2.1 мгновенные (текущие) параметры
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW,  attr_clock,  meth_clock  }, // Часы
    {{1,0,11,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток суммы фаз
    {{1,0,31,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы А
    {{1,0,51,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы B
    {{1,0,71,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы C
    {{1,0,91,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы
    {{1,0,12,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Среднее Напряжение фаз
    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы А
    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы B
    {{1,0,72,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы C
//    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Линейное напряжение АВ
//    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Линейное напряжение CВ
    {{1,0,33,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности фазы А
    {{1,0,53,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности фазы B
    {{1,0,73,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности фазы C
    {{1,0,13,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности общий
    {{1,0,14,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Частота сети
    {{1,0, 9,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Полная мощность
    {{1,0,29,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Полная мощность фазы А
    {{1,0,49,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Полная мощность фазы B
    {{1,0,69,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Полная мощность фазы C
    {{1,0, 1,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная мощность
    {{1,0,21,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная мощность фазы А
    {{1,0,41,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная мощность фазы B
    {{1,0,61,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная мощность фазы C
    {{1,0,03,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная мощность
    {{1,0,23,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная мощность фазы А
    {{1,0,43,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная мощность фазы B
    {{1,0,63,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная мощность фазы C
    {{1,0, 1,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная энергия, импорт
    {{1,0, 2,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная энергия, экспорт
    {{1,0, 3,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная энергия, импорт
    {{1,0, 4,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная энергия, экспорт
    {{1,0,88,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Удельная энергия потерь в цепях тока
    {{1,0,89,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Удельная энергия потерь в силовых трансформаторах
    {{1,0,12,7,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Межфазное напряжение АВ
    {{1,0,12,7,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Межфазное напряжение ВС
    {{1,0,12,7,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Межфазное напряжение АС
    {{1,0,81,7,10,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Угол А-В
    {{1,0,81,7,21,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Угол В-С
    {{1,0,81,7, 2,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Угол С-А
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

const COSEM_OBJECT cosem_objcts_1_0_99_1_0_255[] = { // А2.2 параметры профиля нагрузки
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW,  attr_clock,  meth_clock  }, // Часы
    {{1,0, 1,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Импорт активной энергии за период записи
    {{1,0, 2,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Экспорт активной энергии за период записи
    {{1,0, 3,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, импорт за период записи
    {{1,0, 4,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, экспорт за период записи
//    {{1,0,1,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Импорт активной энергии за период записи
//    {{1,0,2,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Экспорт активной энергии за период записи
//    {{1,0,3,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, импорт за период записи
//    {{1,0,4,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, экспорт за период записи
//    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  meth_1_0_0_29_0_255}, // Напряжение фазы А
//    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  meth_1_0_0_29_0_255}, // Напряжение фазы B
//    {{1,0,72,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  meth_1_0_0_29_0_255}, // Напряжение фазы C
//    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  meth_1_0_0_29_0_255  }, // Линейное напряжение АВ
//    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  meth_1_0_0_29_0_255  }, // Линейное напряжение CВ
//    {{0,0,96,9,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Температура,  С0
//    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Продолжительность записи, сек.
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

const COSEM_OBJECT cosem_objcts_1_0_98_2_0_255[] = { // А2.3 параметры ежесуточного профиля
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW,  attr_clock,      meth_clock }, // Часы
    {{1,0, 1,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт сумме тарифов
    {{1,0, 1,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 1 тарифу
    {{1,0, 1,8,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 2 тарифу
    {{1,0, 1,8,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 3 тарифу
    {{1,0, 1,8,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 4 тарифу
    {{1,0, 1,8,5,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 5 тарифу
    {{1,0, 1,8,6,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 6 тарифу
    {{1,0, 1,8,7,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 7 тарифу
    {{1,0, 1,8,8,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 8 тарифу
    {{1,0, 2,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия -, экспорт сумме тарифов
    {{1,0, 2,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия -, экспорт по 1 тарифу
    {{1,0, 2,8,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия -, экспорт по 2 тарифу
    {{1,0, 2,8,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия -, экспорт по 3 тарифу
    {{1,0, 2,8,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия -, экспорт по 4 тарифу
    {{1,0, 3,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия +, импорт сумме тарифов
    {{1,0, 3,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия +, импорт по 1 тарифу
    {{1,0, 3,8,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия +, импорт по 2 тарифу
    {{1,0, 3,8,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия +, импорт по 3 тарифу
    {{1,0, 3,8,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия +, импорт по 4 тарифу
    {{1,0, 4,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия -, экспорт сумме тарифов
    {{1,0, 4,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия -, экспорт по 1 тарифу
    {{1,0, 4,8,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия -, экспорт по 2 тарифу
    {{1,0, 4,8,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия -, экспорт по 3 тарифу
    {{1,0, 4,8,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия -, экспорт по 4 тарифу
//    {{1,0,88,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Энергия потерь в ЛЭП
//    {{1,0,89,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Энергия потерь в силовых трансформаторах
//    {{0,0,96,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Время некачественной частоты
//    {{0,0,96,5,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Статус некачественной энергии
//    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Время работы счетчика
    {{1,0, 1,6,0,255},  0, DLMS_OBJECT_TYPE_EXTENDED_REGISTER,        PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_ext_value,  0}, // Максимальная мощность за месяц и время пика мощности
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

const COSEM_OBJECT cosem_objcts_1_0_94_7_5_255[] = { // А2.3 параметры телеизмерений профиля
    {{1,0,31,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы А
    {{1,0,51,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы B
    {{1,0,71,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы C
    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы А
    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы B
    {{1,0,72,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы C
    {{1,0, 1,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Суммарная активная мощность
    {{1,0, 3,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Суммарная реактивная мощность
    {{1,0, 9,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Суммарная полная мощность
    {{1,0,13,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

const COSEM_OBJECT cosem_objcts_0_0_99_98_0_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,0,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{1,0,12,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Напряжение любой фазы
    {{1,0,12,7,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Глубина провала/перенапряжения
    {{0,0,96,8,10,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Длительность провала/перенапряжения
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_1_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,1,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_2_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,2,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_3_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,3,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,12,4,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Номер канала(интерфейс)
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_4_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,4,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_5_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,5,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,12,4,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Номер канала (интерфейс)
    {{0,0,96,12,6,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Адрес (клиента)
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_6_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,6,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,12,4,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Номер канала (интерфейс)
    {{0,0,96,12,6,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Адрес (клиента)
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_7_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,7,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_8_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,11,8,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Код события
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_9_255[] = {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,5,1,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Статус качества сети
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};
const COSEM_OBJECT cosem_objcts_0_0_99_98_10_255[]= {
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Дата и время захвата
    {{0,0,96,3,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Статус входов/выходов
    {{0,0,96,8,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW, 0,  0  }, // Время работы счетчика
    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

const COSEM_OBJECT cosem_objcts[] = {
    //основные
    {{0,0,40,0,0,255},  1, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, PDU_DLMS_AUTHENTICATION_NONE, attr_0_0_40_0_0_255, meth_0_0_40_0_0_255 }, // Объект текущего соединения (ОТС)
//    {{0,0,40,0,1,255},  1, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, DLMS_AUTHENTICATION_NONE, attr_0_0_40_0_0_255, meth_0_0_40_0_0_255 }, // Объект текущего соединения (ОТС)
    {{0,0,40,0,2,255},  1, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, PDU_DLMS_AUTHENTICATION_LOW,  attr_0_0_40_0_0_255, meth_0_0_40_0_0_255 }, // Объект текущего соединения (ОТС)
    {{0,0,40,0,3,255},  1, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, PDU_DLMS_AUTHENTICATION_HIGH, attr_0_0_40_0_0_255, meth_0_0_40_0_0_255 }, // Объект текущего соединения (ОТС)
    {{0,0,42,0,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_NONE, attr_0_0_42_0_0_255, 0 }, // Логическое имя устройства
    {{0,0, 1,0,0,255},  0, DLMS_OBJECT_TYPE_CLOCK,                    PDU_DLMS_AUTHENTICATION_NONE, attr_clock,  meth_clock  }, // Часы
//    {{0,0,43,0,0,255},  1, DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP,      DLMS_AUTHENTICATION_NONE, attr_0_0_43_0_0_255, meth_0_0_43_0_0_255 }, // Настройки безопасности

    //Паспортные данные
    {{0,0,96,1,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Серийный номер счетчика
    {{0,0,96,1,1,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Тип счетчика
    {{0,0,96,1,2,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Версия метрологического ПО
    {{0,0,96,1,3,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Версия коммуникационного ПО
    {{1,0, 0,4,2,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Коэффициент трансформации по току
    {{1,0, 0,4,3,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Коэффициент трансформации по напряжению
    {{0,0,96,1,4,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Дата выпуска счетчика
    {{0,0,96,1,5,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Номер выносного дисплея / номер счетчика у дисплея

    //Программируемые параметры и функции
    {{0,1,22,0,0,255},  1, DLMS_OBJECT_TYPE_IEC_HDLC_SETUP,           PDU_DLMS_AUTHENTICATION_LOW,  attr_rs, 0 }, // RS-485-1 // a9 a2
    {{0,2,22,0,0,255},  1, DLMS_OBJECT_TYPE_IEC_HDLC_SETUP,           PDU_DLMS_AUTHENTICATION_LOW,  attr_rs, 0 }, // RS-485-1 // a9 a2
    {{0,0,13,0,0,255},  0, DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR,        PDU_DLMS_AUTHENTICATION_LOW,  attr_tariff, meth_tariff }, // профиль тарифного расписания // a3 a4 a5 a10 m1
    {{0,0,10,0,100,255},0, DLMS_OBJECT_TYPE_SCRIPT_TABLE,             PDU_DLMS_AUTHENTICATION_LOW,  attr_script, 0 }, // скрипты тарифного расписания
    {{0,0,14,0,0,255},  0, DLMS_OBJECT_TYPE_REGISTER_ACTIVATION,      PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_active, 0 }, // активация тарифного расписания
    {{0,0,11,0,0,255},  0, DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE,       PDU_DLMS_AUTHENTICATION_LOW,  attr_spec_days, 0 }, // Таблица специальных дней
//    {{0,0,15,0,0,255},  0, DLMS_OBJECT_TYPE_ACTION_SCHEDULE,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Расчетный день и час //a4
//    {{0,0,12,0,2,255},  0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_display, 0 }, // дисплей, индикация // a3
//    {{0,0,40,0,2,255},  0, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Пароль низкого уровня // a7
//    {{0,0,40,0,3,255},  0, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Пароль высокого уровня // m2
    {{0,0,96,1,10,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Данные точки учета (до 64 байт) // a2
//    {{1,0,0,10,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Активное сопротивление линии // a2 // ошибка в классе СПОДЕС_060317
    {{0,0,17,0,0,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // мощность для отключения // a3
    {{0,0,17,0,1,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // ток для отключения // a6
    {{0,0,17,0,2,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // напряжения для отключения // a6
    {{0,0,17,0,3,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // воздействия магнитного поля для отключения // a6
    {{0,0,17,0,4,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // по разбалансу токов для отключения // a6
    {{0,0,17,0,5,255},  0, DLMS_OBJECT_TYPE_LIMITER,                  PDU_DLMS_AUTHENTICATION_LOW,  attr_limit, 0 }, // по превышению температуры для отключения // a6
    {{1,0,12,31,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Порог для фиксации провала напряжения // a2
    {{1,0,12,35,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Порог для фиксации перенапряжения // a2
    {{1,0,12,39,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Пороговое напряжение для фиксации перерыва питания // a2
//    {{1,0,12,43,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Время перехода напряжения через нижний порог // a2
//    {{1,0,12,44,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Время перехода напряжения через верхний порог // a2
//    {{1,0,12,45,0,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Время пропадания напряжения // a2
    {{1,0,131,35,0,255},0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Порог для фиксации превышения тангенса нагрузки // a2
    {{1,0,133,35,0,255},0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Порог для фиксации коэффициента несимметрии напряжений // a2
    {{1,0, 0,6,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_register_rw, 0 }, // Согласованное напряжение электропитания // a2
    {{1,0, 1,4,0,255},  0, DLMS_OBJECT_TYPE_DEMAND_REGISTER,          PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_demand, meth_reg_demand }, // Период интегрирования максимальной мощности // a8
    {{1,0, 0,8,4,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Период записи в профиль 1 // a2
    {{1,0, 0,8,5,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Период записи в профиль 2 // a2
//    {{0,0,96,4,1,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Режим подсветки ЖКИ // a2
//    {{0,0,96,4,2,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport_rw, 0 }, // Режим телеметрии // a2
//    {{1,0,98,1,0,255},  0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Очистка журнала ежемесячных показаний / Захват показаний на расчетный день и час // m1 m2
//    {{1,0,98,2,0,255},  0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Очистка журнала ежесуточных показаний // m1
    {{0,0,99,98,0,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (напряжение)
    {{0,0,99,98,1,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (ток)
    {{0,0,99,98,2,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (вкл./откл.)
    {{0,0,99,98,3,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (коррекция данных)
    {{0,0,99,98,4,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (внешние воздействия)
    {{0,0,99,98,5,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (коммуникационные события)
    {{0,0,99,98,6,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (контроль доступа)
    {{0,0,99,98,7,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (самодиагностика)
    {{0,0,99,98,8,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (превышение тангенса)
    {{0,0,99,98,9,255}, 1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (качество сети)
    {{0,0,99,98,10,255},1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_event, meth_profile_event }, // Журнал событий (дискретные входы и выходы)
//    {{0,0,99,1,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Очистка профиля 1 // m1
//    {{0,0,99,2,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Очистка профиля 2 // m1
//    {{0,0,99,3,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Очистка профиля 3 // m1
    {{0,0,96,3,10,255}, 0, DLMS_OBJECT_TYPE_DISCONNECT_CONTROL,       PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Режим управления реле отключения абонента // a4
    {{0,0,96,5,3,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_passport, 0 }, // Параметры режима инициативного выхода // a3
    {{0,0,96,8,10,255}, 0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value, 0 }, //
//    // события
//    {{0,0,99,11,0,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала напряжений
//    {{0,0,99,11,1,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала токов
//    {{0,0,99,11,2,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала включений/выключений
//    {{0,0,99,11,4,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала внешних воздействий
//    {{0,0,99,11,5,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала соединений
//    {{0,0,99,11,6,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала несанкционированного доступа
//    {{0,0,99,11,7,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала самодиагностики
//    {{0,0,99,11,8,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала тангенса нагрузки
//    {{0,0,99,11,9,255}, 0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала качества энергии
//    {{0,0,99,11,10,255},0, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  0, 0 }, // Событие журнала состояний входов/выходов

    //обновление прошивки
    {{0,0,44,0,0,255},  0, DLMS_OBJECT_TYPE_IMAGE_TRANSFER,           PDU_DLMS_AUTHENTICATION_LOW, attr_img_transf, meth_img_transf }, // Передача двоичных файлов [Image Transfer] 0.0.44.0.0.255

    //профиль А2.1 мгновенные
    {{1,0,94,7,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, meth_profile_0 }, // Стоп-кадр профиль на 1 запись 1.0.94.7.0.255
    {{1,0,94,7,3,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, 0 }, // Профиль масштаба на 1 запись единицы измерения

    //профиль А2.2 нагрузки
    {{1,0,99,1,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, meth_profile_0 }, // универсальный профиль 1.0.0.8.4.255-настройка
    {{1,0,94,7,4,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, 0 }, // Профиль масштаба на 1 запись единицы измерения

    //профиль А2.3 сутки
    {{1,0,98,2,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, meth_profile_0 }, // ежесуточный профиль
    {{1,0,99,2,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, meth_profile_0 }, // ежесуточный профиль // А3.3
    {{1,0,94,7,2,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, 0 }, // Профиль масштаба на 1 запись единицы измерения

    //профиль А2.4 месяц
    {{1,0,98,1,0,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, meth_profile_0 }, // ежемесячный профиль
    {{1,0,94,7,1,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_profile_0, 0 }, // Профиль масштаба на 1 запись единицы измерения

    //профиль А2.5 хрень
//    {{1,0,94,7,5,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_1_0_99_1_0_255, meth_1_0_99_1_0_255 }, // телеизмерений профиль
//    {{1,0,94,7,6,255},  1, DLMS_OBJECT_TYPE_PROFILE_GENERIC,          PDU_DLMS_AUTHENTICATION_LOW,  attr_1_0_99_1_0_255, meth_1_0_99_1_0_255 }, // телесигнализации профиль

    //events
    {{0,0,96,2,0,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event }, // todo get,set,meth
    {{0,0,96,2,1,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,2,5,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,2,7,255},  0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,2,12,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,2,13,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,0,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,1,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,2,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,3,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,5,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,6,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,7,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,8,255}, 0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,15,255},0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,16,255},0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,17,255},0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },
    {{0,0,96,20,18,255},0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_LOW,  attr_event, meth_event },

    {{0,0,96,9,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Температура
//    {{1,0, 1,4,0,255},  0, DLMS_OBJECT_TYPE_DEMAND_REGISTER,          PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Температура

    // радио интерфейс    
    {{0,0,96,1,254,255},0, DLMS_OBJECT_TYPE_DATA,                     PDU_DLMS_AUTHENTICATION_NONE, attr_radio_bridge, 0 }, // 

// сподес
//    {{1,0,31,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы А
//    {{1,0,51,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы B
//    {{1,0,71,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Ток фазы C
//    {{1,0,32,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы А
//    {{1,0,52,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы B
//    {{1,0,72,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Напряжение фазы C
//    {{1,0,13,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Коэффициент мощности общий
//    {{1,0,14,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Частота сети
//    {{1,0, 9,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Полная мощность
//    {{1,0, 1,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная мощность
//    {{1,0,03,7,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная мощность
//    {{1,0, 1,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Активная энергия, импорт
//    {{1,0, 1,8,1,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 1 тарифу
//    {{1,0, 1,8,2,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 2 тарифу
//    {{1,0, 1,8,3,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 3 тарифу
//    {{1,0, 1,8,4,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 4 тарифу
//    {{1,0, 1,8,5,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 5 тарифу
//    {{1,0, 1,8,6,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 6 тарифу
//    {{1,0, 1,8,7,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 7 тарифу
//    {{1,0, 1,8,8,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Активная энергия +, импорт по 8 тарифу
//    {{1,0, 3,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная энергия, импорт
//    {{1,0, 4,8,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0  }, // Реактивная энергия, экспорт
    {{1,0,1,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Импорт активной энергии за период записи
    {{1,0,2,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Экспорт активной энергии за период записи
    {{1,0,3,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, импорт за период записи
    {{1,0,4,29,0,255},  0, DLMS_OBJECT_TYPE_REGISTER,                 PDU_DLMS_AUTHENTICATION_LOW,  attr_reg_value,  0}, // Реактивная энергия, экспорт за период записи

    {{0,0,0,0,0,0},0,0,0,0,0} // end
};

//Соединение типа «Публичный клиент» должно содержать следующие объекты:
//	Логическое имя устройства;
//	Значение часов реального времени в счётчике;
//	Соединение типа «Считыватель показаний» должно содержать следующие объекты:
//	Профили объектов, позволяющие накапливать данные, определенные списком па-раметров из приложений A2, A3, A4, A5, A6.
//	Объекты, предоставляющие оперативный доступ к элементам в текущем списке па-раметров. Обязателен селективный доступ к объектам профилей.
//	Сервис «Action» должен использовать только 2 метода:
//	Метод 6 (сдвиг времени) класса 0008 объекта 0.0.1.0.0.255 (локальное время счетчика). Метод можно использовать не чаще, чем 1 раз в сутки;
//	Метод 2 (захват) класса 0007 объекта 1.0.94.07.0.255 (профиль текущих значений).
//	Соединение типа «Конфигуратор» должно содержать следующие объекты:
//	На чтение - все объекты.
//	На запись - объекты, указанные в приложении А4.
//Перечень объектов для каждого типа соединения подробно описан в приложениях A2, A3, A4, A5.
//	Права доступа к каждому объекту данных также описаны в приложениях A2, A3, A4, A5.

//трехфазники
// Таблица А2.1 — мгновенные (текущие) параметры    1.0.94.7.0.255      масш 1.0.94.7.3.255
// Таблица А2.2 – параметры профиля нагрузки        1.0.99.1.0.255      масш 1.0.94.7.4.255 конфиг 1.0.0.8.4.255
// Таблица А2.3 – параметры ежесуточного профиля    1.0.98.2.0.255      масш?1.0.94.7.2.255
// Таблица А2.4 – Параметры ежемесячного профиля    1.0.98.1.0.255      масш 1.0.94.7.1.255
// Таблица А2.5 – Параметры профиля телеизмерений   1.0.94.7.6.255
//однофазники
// Таблица А3.1 – Текущие значения                  1.0.94.7.0.255           1.0.94.7.3.255
// Таблица А3.2 – Пар. профиля нагрузки за период   1.0.99.1.0.255      масш 1.0.94.7.4.255 конфиг 1.0.0.8.4.255
// Таблица А3.3 – Пар. профиля нагрузки за сутки    1.0.99.2.0.255      масш 1.0.94.7.3.255
// Таблица А3.4 – параметры ежемесячного профиля    1.0.98.1.0.255      масш 1.0.94.7.10.255
