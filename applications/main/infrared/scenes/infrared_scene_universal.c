#include "../infrared_i.h"

typedef enum {
	SubmenuIndexUniversalMyTV,
    SubmenuIndexUniversalTV,
    SubmenuIndexUniversalAC,
    SubmenuIndexUniversalAudio,
} SubmenuIndex;

static void infrared_scene_universal_submenu_callback(void* context, uint32_t index) {
    Infrared* infrared = context;
    view_dispatcher_send_custom_event(infrared->view_dispatcher, index);
}

void infrared_scene_universal_on_enter(void* context) {
    Infrared* infrared = context;
    Submenu* submenu = infrared->submenu;

    submenu_add_item(
        submenu,
        "My TV",
        SubmenuIndexUniversalMyTV,
        infrared_scene_universal_submenu_callback,
        context);
    submenu_add_item(
        submenu,
        "TVs",
        SubmenuIndexUniversalTV,
        infrared_scene_universal_submenu_callback,
        context);
    submenu_add_item(
        submenu,
        "Audio Players",
        SubmenuIndexUniversalAudio,
        infrared_scene_universal_submenu_callback,
        context);
    submenu_add_item(
        submenu,
        "Air Conditioners",
        SubmenuIndexUniversalAC,
        infrared_scene_universal_submenu_callback,
        context);
    submenu_set_selected_item(submenu, 0);

    view_dispatcher_switch_to_view(infrared->view_dispatcher, InfraredViewSubmenu);
}

bool infrared_scene_universal_on_event(void* context, SceneManagerEvent event) {
    Infrared* infrared = context;
    SceneManager* scene_manager = infrared->scene_manager;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexUniversalMyTV) {
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalMyTV);
            consumed = true;
        } else if(event.event == SubmenuIndexUniversalTV) {
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalTV);
            consumed = true;
        } else if(event.event == SubmenuIndexUniversalAC) {
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalAC);
            consumed = true;
        } else if(event.event == SubmenuIndexUniversalAudio) {
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalAudio);
            consumed = true;
        }
    }

    return consumed;
}

void infrared_scene_universal_on_exit(void* context) {
    Infrared* infrared = context;
    submenu_reset(infrared->submenu);
}
