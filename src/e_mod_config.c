#include <e.h>
#include <Elementary.h>
#include "e_mod_config.h"

/* Local Function Prototypes */
static void *_create_data(E_Config_Dialog *cfd);
static void _free_data(E_Config_Dialog *cfd, E_Config_Dialog_Data *cfdata);
static void _fill_data(E_Config_Dialog_Data *cfdata);
static Evas_Object *_basic_create(E_Config_Dialog *cfd, Evas *evas, E_Config_Dialog_Data *cfdata);
static int _basic_apply(E_Config_Dialog *cfd, E_Config_Dialog_Data *cfdata);
/* External Functions */

/* Function for calling our personal dialog menu */
E_Config_Dialog *
e_int_config_productivity_module(E_Container *con, const char *params) 
{
   E_Config_Dialog *cfd = NULL;
   E_Config_Dialog_View *v = NULL;
   char buf[PATH_MAX];

   /* is this config dialog already visible ? */
   if (e_config_dialog_find("Productivity", "advanced/productivity")) return NULL;

   v = E_NEW(E_Config_Dialog_View, 1);
   if (!v) return NULL;

   v->create_cfdata = _create_data;
   v->free_cfdata = _free_data;
   v->basic.create_widgets = _basic_create;
   v->basic.apply_cfdata = _basic_apply;

   /* Icon in the theme */
   snprintf(buf, sizeof(buf), "%s/e-module-productivity.edj", productivity_conf->module->dir);

   /* create our config dialog */
   cfd = e_config_dialog_new(con, _("Productivity Module"), "Productivity", 
                             "advanced/productivity", buf, 0, v, NULL);

   e_dialog_resizable_set(cfd->dia, 1);
   e_win_size_min_set(cfd->dia->win, 333, 400);
   e_win_resize(cfd->dia->win, 540, 400);
   productivity_conf->cfd = cfd;
   return cfd;
}

/* Local Functions */
static void *
_create_data(E_Config_Dialog *cfd) 
{
   char buf[PATH_MAX];
   E_Config_Dialog_Data *cfdata = NULL;
   
   cfdata = E_NEW(E_Config_Dialog_Data, 1);
   
   e_mod_config_schedule_create_data(cfdata);
   e_mod_config_worktools_create_data(cfdata);
   return cfdata;
}

static void 
_free_data(E_Config_Dialog *cfd, E_Config_Dialog_Data *cfdata) 
{
   productivity_conf->cfd = NULL;
   E_FREE(cfdata);
}

static void 
_fill_data(E_Config_Dialog_Data *cfdata) 
{
   /* load a temp copy of the config variables */
}

//TODO:remove this after calendar is implemented
static void
_item_2_pressed(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *bx = data;
   Evas_Object *cal;
   
   elm_box_clear(bx);
   
   cal = elm_calendar_add(bx);
   evas_object_size_hint_weight_set(cal, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(cal, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, cal);
   evas_object_show(cal);
}

static Evas_Object *
_basic_create(E_Config_Dialog *cfd, Evas *evas, E_Config_Dialog_Data *cfdata) 
{
   Evas_Object *otb;

   INF("PROD_LOG_CONFIG:%d\n", _productivity_log);
   otb = e_widget_toolbook_add(evas, 24, 24);

   e_mod_config_schedule_new(otb, evas, cfdata);
   e_mod_config_worktools_new(otb, evas, cfdata);

   e_widget_toolbook_page_show(otb, 0);

   return otb;
}

static int 
_basic_apply(E_Config_Dialog *cfd, E_Config_Dialog_Data *cfdata) 
{
   e_mod_config_worktools_save(cfdata);
   e_mod_config_schedule_save_config(cfdata);
   e_config_save_queue();
   return 1;
}

