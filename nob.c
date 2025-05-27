#define NOB_IMPLEMENTATION
#include "nob.h"

//__________________________________
// DEBUG variable
bool DEBUG = false;
const char *DEBUG_FLAG = "-DDEBUG=0";

void set_debug_flag()
{
    DEBUG_FLAG = DEBUG ? "-DDEBUG=1" : "-DDEBUG=0";
}
//__________________________________
// SCREEN_W and SCREEN_H variables
#define SCREEN_W "1280"
#define SCREEN_H "720"
const char *GAME_WIDTH_CONFIG = "-DWINDOW_WIDTH=" SCREEN_W;
const char *GAME_HEIGHT_CONFIG = "-DWINDOW_HEIGHT=" SCREEN_H;

//__________________________________
// MinilibX .c files
const char *mlx_cfiles[] = {
    "./src/libs/minilibx/mlx_init.c",
    "./src/libs/minilibx/mlx_new_window.c",
    "./src/libs/minilibx/mlx_pixel_put.c",
    "./src/libs/minilibx/mlx_loop.c",
    "./src/libs/minilibx/mlx_mouse_hook.c",
    "./src/libs/minilibx/mlx_key_hook.c",
    "./src/libs/minilibx/mlx_expose_hook.c",
    "./src/libs/minilibx/mlx_loop_hook.c",
    "./src/libs/minilibx/mlx_int_anti_resize_win.c",
    "./src/libs/minilibx/mlx_int_do_nothing.c",
    "./src/libs/minilibx/mlx_int_wait_first_expose.c",
    "./src/libs/minilibx/mlx_int_get_visual.c",
    "./src/libs/minilibx/mlx_flush_event.c",
    "./src/libs/minilibx/mlx_string_put.c",
    "./src/libs/minilibx/mlx_set_font.c",
    "./src/libs/minilibx/mlx_new_image.c",
    "./src/libs/minilibx/mlx_get_data_addr.c",
    "./src/libs/minilibx/mlx_put_image_to_window.c",
    "./src/libs/minilibx/mlx_get_color_value.c",
    "./src/libs/minilibx/mlx_clear_window.c",
    "./src/libs/minilibx/mlx_xpm.c",
    "./src/libs/minilibx/mlx_int_str_to_wordtab.c",
    "./src/libs/minilibx/mlx_destroy_window.c",
    "./src/libs/minilibx/mlx_int_param_event.c",
    "./src/libs/minilibx/mlx_int_set_win_event_mask.c",
    "./src/libs/minilibx/mlx_hook.c",
    "./src/libs/minilibx/mlx_rgb.c",
    "./src/libs/minilibx/mlx_destroy_image.c",
    "./src/libs/minilibx/mlx_mouse.c",
    "./src/libs/minilibx/mlx_screen_size.c",
    "./src/libs/minilibx/mlx_destroy_display.c",
};

//__________________________________
// MinilibX .o files array
const char *mlx_ofiles[NOB_ARRAY_LEN(mlx_cfiles)];

//__________________________________
// Libftx .c files
const char *libftx_cfiles[] = {
    "./src/libs/libftx/src/char/chr_closequote_idx.c",
    "./src/libs/libftx/src/char/chr_equals.c",
    "./src/libs/libftx/src/char/chr_isalnum.c",
    "./src/libs/libftx/src/char/chr_isalpha.c",
    "./src/libs/libftx/src/char/chr_isascii.c",
    "./src/libs/libftx/src/char/chr_isdigit.c",
    "./src/libs/libftx/src/char/chr_isprint.c",
    "./src/libs/libftx/src/char/chr_isquote.c",
    "./src/libs/libftx/src/char/chr_issign.c",
    "./src/libs/libftx/src/char/chr_isspace.c",
    "./src/libs/libftx/src/char/chr_istoken.c",
    "./src/libs/libftx/src/char/chr_tolower.c",
    "./src/libs/libftx/src/char/chr_toupper.c",
    "./src/libs/libftx/src/converter/ft_atoi.c",
    "./src/libs/libftx/src/converter/ft_boolstr.c",
    "./src/libs/libftx/src/converter/ft_itoa.c",
    "./src/libs/libftx/src/converter/ft_itoa_base.c",
    "./src/libs/libftx/src/converter/ft_itohex.c",
    "./src/libs/libftx/src/converter/ft_uitoa.c",
    "./src/libs/libftx/src/converter/ft_ultoa_base.c",
    "./src/libs/libftx/src/env/env_load.c",
    "./src/libs/libftx/src/env/env_search.c",
    "./src/libs/libftx/src/files/file_gen.c",
    "./src/libs/libftx/src/files/file_utils.c",
    "./src/libs/libftx/src/files/ft_readfile.c",
    "./src/libs/libftx/src/ft_isdebug.c",
    "./src/libs/libftx/src/getnextline/get_next_line.c",
    "./src/libs/libftx/src/getnextline/get_next_line_utils.c",
    "./src/libs/libftx/src/int/array/int_clear.c",
    "./src/libs/libftx/src/int/array/int_populate.c",
    "./src/libs/libftx/src/int/array/int_print.c",
    "./src/libs/libftx/src/int/array/int_search.c",
    "./src/libs/libftx/src/int/ft_int_minmax_idx.c",
    "./src/libs/libftx/src/int/ft_intcmp.c",
    "./src/libs/libftx/src/int/int_free.c",
    "./src/libs/libftx/src/int/int_imax.c",
    "./src/libs/libftx/src/int/int_imin.c",
    "./src/libs/libftx/src/lists/lst_count.c",
    "./src/libs/libftx/src/lists/lst_create.c",
    "./src/libs/libftx/src/lists/lst_delete.c",
    "./src/libs/libftx/src/lists/lst_delete2.c",
    "./src/libs/libftx/src/lists/lst_get.c",
    "./src/libs/libftx/src/lists/lst_print.c",
    "./src/libs/libftx/src/lists/lst_search.c",
    "./src/libs/libftx/src/lists/lst_split.c",
    "./src/libs/libftx/src/lists/lst_to_strmtx.c",
    "./src/libs/libftx/src/lists/lst_upsert.c",
    "./src/libs/libftx/src/math/ft_iabs.c",
    "./src/libs/libftx/src/math/ft_ipow.c",
    "./src/libs/libftx/src/math/ft_nbr_len.c",
    "./src/libs/libftx/src/math/ft_ulnbr_len.c",
    "./src/libs/libftx/src/memory/ft_bzero.c",
    "./src/libs/libftx/src/memory/ft_calloc.c",
    "./src/libs/libftx/src/memory/ft_free.c",
    "./src/libs/libftx/src/memory/ft_freemtx.c",
    "./src/libs/libftx/src/memory/ft_getaddr.c",
    "./src/libs/libftx/src/memory/ft_memchr.c",
    "./src/libs/libftx/src/memory/ft_memcmp.c",
    "./src/libs/libftx/src/memory/ft_memcpy.c",
    "./src/libs/libftx/src/memory/ft_memmove.c",
    "./src/libs/libftx/src/memory/ft_memrev.c",
    "./src/libs/libftx/src/memory/ft_memset.c",
    "./src/libs/libftx/src/printf/ft_pfflag.c",
    "./src/libs/libftx/src/printf/ft_pflaghandler.c",
    "./src/libs/libftx/src/printf/ft_printf.c",
    "./src/libs/libftx/src/printf/ft_printf_core.c",
    "./src/libs/libftx/src/printf/pf_errcode.c",
    "./src/libs/libftx/src/pthread/mutex/mutex_getters.c",
    "./src/libs/libftx/src/pthread/mutex/mutex_increments.c",
    "./src/libs/libftx/src/pthread/mutex/mutex_setters.c",
    "./src/libs/libftx/src/pthread/mutex/mutex_wrapper.c",
    "./src/libs/libftx/src/str/str_chr.c",
    "./src/libs/libftx/src/str/str_clearquotes.c",
    "./src/libs/libftx/src/str/str_cmp.c",
    "./src/libs/libftx/src/str/str_count_c.c",
    "./src/libs/libftx/src/str/str_dup.c",
    "./src/libs/libftx/src/str/str_endswith.c",
    "./src/libs/libftx/src/str/str_equals.c",
    "./src/libs/libftx/src/str/str_every.c",
    "./src/libs/libftx/src/str/str_freejoin.c",
    "./src/libs/libftx/src/str/str_idxofchar.c",
    "./src/libs/libftx/src/str/str_idxofstr.c",
    "./src/libs/libftx/src/str/str_ilen.c",
    "./src/libs/libftx/src/str/str_includesset.c",
    "./src/libs/libftx/src/str/str_isblank.c",
    "./src/libs/libftx/src/str/str_ischar_inquotes.c",
    "./src/libs/libftx/src/str/str_isvariable.c",
    "./src/libs/libftx/src/str/str_iteri.c",
    "./src/libs/libftx/src/str/str_join.c",
    "./src/libs/libftx/src/str/str_lcat.c",
    "./src/libs/libftx/src/str/str_lcpy.c",
    "./src/libs/libftx/src/str/str_mapi.c",
    "./src/libs/libftx/src/str/str_mtxcpy.c",
    "./src/libs/libftx/src/str/str_mtxdup.c",
    "./src/libs/libftx/src/str/str_mtxlen.c",
    "./src/libs/libftx/src/str/str_mtxpush.c",
    "./src/libs/libftx/src/str/str_nstr.c",
    "./src/libs/libftx/src/str/str_pad.c",
    "./src/libs/libftx/src/str/str_pushchar.c",
    "./src/libs/libftx/src/str/str_rchr.c",
    "./src/libs/libftx/src/str/str_replace.c",
    "./src/libs/libftx/src/str/str_replace_first.c",
    "./src/libs/libftx/src/str/str_split.c",
    "./src/libs/libftx/src/str/str_startswith.c",
    "./src/libs/libftx/src/str/str_substr.c",
    "./src/libs/libftx/src/str/str_tolower.c",
    "./src/libs/libftx/src/str/str_toupper.c",
    "./src/libs/libftx/src/str/str_trim.c",
    "./src/libs/libftx/src/str/str_ulen.c",
    "./src/libs/libftx/src/str/str_var_ending_idx.c",
    "./src/libs/libftx/src/strict/strict_atoi.c",
    "./src/libs/libftx/src/sys/sys_time.c",
    "./src/libs/libftx/src/unistd/ft_putaddr_fd.c",
    "./src/libs/libftx/src/unistd/ft_putchar_fd.c",
    "./src/libs/libftx/src/unistd/ft_putendl_fd.c",
    "./src/libs/libftx/src/unistd/ft_putnbr_fd.c",
    "./src/libs/libftx/src/unistd/ft_putnchars_fd.c",
    "./src/libs/libftx/src/unistd/ft_putstr_fd.c",
    "./src/libs/libftx/src/unistd/ft_putstrmtx.c",
    "./src/libs/libftx/src/unistd/ft_writeulbase_fd.c"};

//__________________________________
// Libftx .o files array
const char *libftx_ofiles[NOB_ARRAY_LEN(libftx_cfiles)];

//__________________________________
// Cub3D .c files
const char *cubed_src[] = {
    "src/cleanup.c",
    "src/deltatime.c",
    "src/draw_helpers/draw_line.c",
    "src/draw_helpers/draw_pixel.c",
    "src/draw_helpers/draw_rectangle.c",
    "src/init_config.c",
    "src/messages/parse_error_msg.c",
    "src/mlx_engine/events/camera_horizontal_event.c",
    "src/mlx_engine/events/camera_vertical_event.c",
    "src/mlx_engine/events/mouse_movement_event.c",
    "src/mlx_engine/events/movement_horizontal_event.c",
    "src/mlx_engine/events/movement_vertical_event.c",
    "src/mlx_engine/events/player_sprites_events.c",
    "src/mlx_engine/game_loop.c",
    "src/mlx_engine/key_events.c",
    "src/mlx_engine/mlx_setup.c",
    "src/parsing/parse.c",
    "src/parsing/parse_config_utils.c",
    "src/parsing/parse_config_value.c",
    "src/parsing/parse_configs.c",
    "src/parsing/parse_map.c",
    "src/parsing/parse_path_utils.c",
    "src/parsing/parse_utils.c",
    "src/rendering/raycasting/raycasting_init.c",
    "src/rendering/raycasting/raycasting_utils.c",
    "src/rendering/render.c",
    "src/rendering/render_crosshair.c",
    "src/rendering/render_minimap.c",
    "src/rendering/render_sprites.c",
    "src/texture.c",
    "src/utils/color_utils.c",
    "src/utils/map_utils.c",
    "src/utils/math_utils.c",
    "src/utils/mouse_utils.c",
    "src/utils/player_utils.c",
    "src/utils/point_utils.c"};

int build_libft()
{
    Nob_Cmd cmd = {0};

    if (!nob_file_exists("./src/libs/libftx/libft.a") || nob_needs_rebuild("src/libs/libftx/libft.a", libftx_cfiles, NOB_ARRAY_LEN(libftx_cfiles)))
    {
        Nob_String_Builder objs = {0};

        for (size_t i = 0; i < NOB_ARRAY_LEN(libftx_cfiles); ++i)
        {
            nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-Werror", "-g");
            nob_cmd_append(&cmd, "-I./src/includes", "-I./src/libs/libftx/includes", DEBUG_FLAG);

            Nob_String_Builder sb = {0};
            Nob_String_View v = nob_sv_from_cstr(libftx_cfiles[i]);

            if (nob_sv_end_with(v, ".c"))
            {
                Nob_String_View file_no_ext = nob_sv_from_parts(libftx_cfiles[i], strlen(libftx_cfiles[i]) - 2);
                nob_sb_append_buf(&sb, file_no_ext.data, file_no_ext.count);
                nob_sb_append_cstr(&sb, ".o");

                const char *object_file = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));

                nob_cmd_append(&cmd, "-c", libftx_cfiles[i]);
                nob_cmd_append(&cmd, "-o", object_file);

                if (!nob_cmd_run_sync_and_reset(&cmd))
                {
                    return 1;
                }
                libftx_ofiles[i] = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));
                sb = (Nob_String_Builder){0};
            }
        }
        libftx_ofiles[NOB_ARRAY_LEN(libftx_cfiles)] = NULL;

        nob_cmd_append(&cmd, "ar", "rcs", "src/libs/libftx/libft.a");
        for (size_t i = 0; i < NOB_ARRAY_LEN(libftx_ofiles); ++i)
        {
            nob_cmd_append(&cmd, libftx_ofiles[i]);
        }
        if (!nob_cmd_run_sync_and_reset(&cmd))
        {
            return 1;
        }
    }

    return 0;
}

int build_mlx()
{

    Nob_Cmd cmd = {0};
    bool need_to_download_mlx = !nob_file_exists("src/libs/minilibx/");
    if (need_to_download_mlx)
    {
        const char *zip_name = "minilibx-linux.zip";
        const char *mlx_link = "https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip";

        if (!nob_file_exists(zip_name))
        {
            nob_cmd_append(&cmd, "wget", mlx_link, "-O", (char *)zip_name, NULL);
            if (!nob_cmd_run_sync_and_reset(&cmd))
            {
                return 1;
            }
        }

        if (nob_file_exists(zip_name))
        {
            nob_cmd_append(&cmd, "unzip", (char *)zip_name, NULL);
            if (!nob_cmd_run_sync_and_reset(&cmd))
            {
                return 1;
            }
        }
    }

    bool need_to_compile_mlx = !nob_file_exists("src/libs/minilibx/libmlx.a") || nob_needs_rebuild("src/libs/minilibx/libmlx.a", mlx_cfiles, NOB_ARRAY_LEN(mlx_cfiles));

    if (need_to_compile_mlx)
    {
        const char *zip_name = "minilibx-linux.zip";
        const char *mlx_link = "https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip";

        if (!nob_file_exists("src/libs/minilibx/mlx.h") && !nob_copy_directory_recursively("minilibx-linux-master", "src/libs/minilibx"))
        {
            return 1;
        }
        nob_cmd_append(&cmd, "rm", "-f", (char *)zip_name, NULL);
        if (!nob_cmd_run_sync_and_reset(&cmd))
        {
            return 1;
        }
        nob_cmd_append(&cmd, "rm", "-rf", (char *)"minilibx-linux-master", NULL);
        if (!nob_cmd_run_sync_and_reset(&cmd))
        {
            return 1;
        }
        for (size_t i = 0; i < NOB_ARRAY_LEN(mlx_cfiles); ++i)
        {
            nob_cmd_append(&cmd, "cc", "-O3", "-I/usr/include");
            Nob_String_View src = nob_sv_from_cstr(mlx_cfiles[i]);
            Nob_String_Builder sb = {0};

            if (nob_sv_end_with(src, ".c"))
            {
                Nob_String_View file_no_ext = nob_sv_from_parts(mlx_cfiles[i], strlen(mlx_cfiles[i]) - 2);
                nob_sb_append_buf(&sb, file_no_ext.data, file_no_ext.count);
                nob_sb_append_cstr(&sb, ".o");

                const char *object_file = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));

                nob_cmd_append(&cmd, "-c", mlx_cfiles[i]);
                nob_cmd_append(&cmd, "-o", object_file);

                if (!nob_cmd_run_sync_and_reset(&cmd))
                {
                    return 1;
                }
                mlx_ofiles[i] = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));
                sb = (Nob_String_Builder){0};
            }
        }
        mlx_ofiles[NOB_ARRAY_LEN(mlx_cfiles)] = NULL;

        nob_cmd_append(&cmd, "ar", "rcs", "src/libs/minilibx/libmlx.a");
        for (size_t i = 0; i < NOB_ARRAY_LEN(mlx_ofiles); ++i)
        {
            nob_cmd_append(&cmd, mlx_ofiles[i]);
        }

        if (!nob_cmd_run_sync_and_reset(&cmd))
        {
            return 1;
        }
        // TODO: Uncomment this section if you want to copy the libmlx.a to a uname-specific archive
        // ATM i was receiveing the error: "[INFO] CMD: cp src/libs/minilibx/libmlx.a src/libs/minilibx/libmlx_Linux.a
        //*** stack smashing detected ***: terminated"

        // const char *uname = getenv("UNAME");
        // if (!uname)
        //     uname = "Linux";
        // Nob_String_Builder sb = {0};
        // nob_sb_append_cstr(&sb, "src/libs/minilibx/libmlx_");
        // nob_sb_append_cstr(&sb, uname);
        // nob_sb_append_cstr(&sb, ".a");
        // const char *uname_path = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));

        // nob_cmd_append(&cmd, "cp", "src/libs/minilibx/libmlx.a", uname_path);
        // if (!nob_cmd_run_sync_and_reset(&cmd))
        // {
        //     nob_log(NOB_ERROR, "Failed to copy libmlx.a to uname-specific archive");
        //     return 1;
        // }
    }

    return 0;
}

int build_cub3D()
{
    Nob_Cmd cmd = {0};

    nob_cmd_append(&cmd, "cc", "main.c");
    nob_cmd_append(&cmd, "-Wall", "-Wextra", "-Werror", "-g", "-I./src/includes", "-I./src/libs/libftx/includes", "-I./src/libs/minilibx");
    nob_cmd_append(&cmd, DEBUG_FLAG, GAME_WIDTH_CONFIG, GAME_HEIGHT_CONFIG);

    for (size_t i = 0; i < NOB_ARRAY_LEN(cubed_src); ++i)
    {
        nob_cmd_append(&cmd, cubed_src[i]);
    }

    nob_cmd_append(&cmd, "-o", "cub3D");
    nob_cmd_append(&cmd, "-L./src/libs/libftx", "-lft");
    nob_cmd_append(&cmd, "-L./src/libs/minilibx", "-lmlx");
    nob_cmd_append(&cmd, "-lm", "-lpthread", "-ldl", "-lX11", "-lXext");

    if (!nob_file_exists("cub3D") || nob_needs_rebuild("cub3D", cubed_src, NOB_ARRAY_LEN(cubed_src)))
    {
        if (!nob_cmd_run_sync_and_reset(&cmd))
        {
            nob_log(NOB_ERROR, "Compilation failed.");
            return 1;
        }
    }
    else
    {
        nob_log(NOB_INFO, "%s is up to date. No need to rebuild.", "cub3D");
        return 0;
    }
    return 0;
}

void clean_files()
{
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "rm", "-rf");

    for (size_t i = 0; i < NOB_ARRAY_LEN(libftx_cfiles); ++i)
    {
        Nob_String_Builder sb = {0};
        Nob_String_View v = nob_sv_from_cstr(libftx_cfiles[i]);
        if (nob_sv_end_with(v, ".c"))
        {
            Nob_String_View file_no_ext = nob_sv_from_parts(libftx_cfiles[i], strlen(libftx_cfiles[i]) - 2);
            nob_sb_append_buf(&sb, file_no_ext.data, file_no_ext.count);
            nob_sb_append_cstr(&sb, ".o");
            const char *object_file = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));
            nob_cmd_append(&cmd, object_file);
        }
    }

    for (size_t i = 0; i < NOB_ARRAY_LEN(mlx_cfiles); ++i)
    {
        Nob_String_Builder sb = {0};
        Nob_String_View v = nob_sv_from_cstr(mlx_cfiles[i]);
        if (nob_sv_end_with(v, ".c"))
        {
            Nob_String_View file_no_ext = nob_sv_from_parts(mlx_cfiles[i], strlen(mlx_cfiles[i]) - 2);
            nob_sb_append_buf(&sb, file_no_ext.data, file_no_ext.count);
            nob_sb_append_cstr(&sb, ".o");
            const char *object_file = nob_temp_sv_to_cstr(nob_sb_to_sv(sb));
            nob_cmd_append(&cmd, object_file);
        }
    }

    nob_cmd_append(&cmd, "src/libs/libftx/libft.a", "src/libs/minilibx/libmlx.a", "cub3D", NULL);
    if (!nob_cmd_run_sync_and_reset(&cmd))
    {
        nob_log(NOB_ERROR, "Failed to clean up build files.");
        return;
    }
    nob_log(NOB_INFO, "Build files cleaned up successfully.");

    return;
}
int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    char *exec_name = argv[0];

    nob_shift(argv, argc);

    if (argc == 0)
    {
        if (build_libft())
            return 1;
        if (build_mlx())
            return 1;
        if (build_cub3D())
            return 1;
        return 0;
    }

    while (argc > 0)
    {
        const char *arg = nob_shift(argv, argc);

        if (!strcmp(arg, "--clean"))
        {
            clean_files();
            return 0;
        }

        if (!strcmp(arg, "--debug"))
        {
            DEBUG = true;
            set_debug_flag();
            continue;
        }

        if (!strcmp(arg, "--re"))
        {
            clean_files();
            break;
        }

        if (!strcmp(arg, "--help") || !strcmp(arg, "-h"))
        {
            printf("Usage: %s [Options]\n", exec_name);
            printf("Options:\n");
            printf("  --debug   Enables debug logging\n");
            printf("  --clean   Cleans up build files\n");
            printf("  --re      Cleans up build files and rebuild project\n");
            printf("  --help    Show this help message\n");
            return 0;
        }

        printf("Usage: %s [Options]\n", exec_name);
        printf("Try '%s --help' for more information.\n", exec_name);
        return 1;
    }

    if (build_libft())
        return 1;
    if (build_mlx())
        return 1;
    if (build_cub3D())
        return 1;

    return 0;
}
