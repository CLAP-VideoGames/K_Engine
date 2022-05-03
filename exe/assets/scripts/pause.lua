function getMasterVolume()
    local audioMan2 = AudioManager.getAudioMan();
    return tostring(audioMan2:getMasterVolume());
end

function getMusicVolume()
    local audioMan2 = AudioManager.getAudioMan();
    return tostring(audioMan2:getMusicVolume());
end

function getSFXVolume()
    local audioMan2 = AudioManager.getAudioMan();
    return tostring(audioMan2:getSFXVolume());
end

pause = {
    masterVolumeText = {
        Transform = {
            position = "0.1, 0.1, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Text = {
            overlayName = "MasterVolumeText",
            x = "0.1",
            y = "0.1",
            width = "0.1",
            height = "0.1",
            text = "Master Volume",
            fontName = "MyFont",
            textColor = "0.0, 0.0, 0.0"
        }
    },
    masterVolume = {
        Transform = {
            position = "0.1, 0.2, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Slider = {
            overlayName = "MasterVolumeSlider",
            imageName = "DefaultButton",
            width = "0.4",
            height = "0.1",
            onSliderClick = "setMasterVolume",
            initialPosition = getMasterVolume()
        }
    },
    musicVolumeText = {
        Transform = {
            position = "0.1, 0.3, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Text = {
            overlayName = "MusicVolumeText",
            x = "0.1",
            y = "0.3",
            width = "0.3",
            height = "0.1",
            text = "Music Volume",
            fontName = "MyFont",
            textColor = "0.0, 0.0, 0.0"
        }
    },
    musicVolume = {
        Transform = {
            position = "0.1, 0.4, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Slider = {
            overlayName = "MasterVolumeSlider",
            imageName = "DefaultButton",
            width = "0.4",
            height = "0.1",
            onSliderClick = "setMusicVolume",
            initialPosition = getMusicVolume()
        }
    },
    effectsVolumeText = {
        Transform = {
            position = "0.1, 0.5, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Text = {
            overlayName = "EffectsVolumeText",
            x = "0.1",
            y = "0.5",
            width = "0.3",
            height = "0.1",
            text = "Effects Volume",
            fontName = "MyFont",
            textColor = "0.0, 0.0, 0.0"
        }
    },
    effectsVolume = {
        Transform = {
            position = "0.1, 0.6, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Slider = {
            overlayName = "MasterVolumeSlider",
            imageName = "DefaultButton",
            width = "0.4",
            height = "0.1",
            onSliderClick = "setEffectsVolume",
            initialPosition = getSFXVolume()
        }
    },
    mainMenuButton = {
        Transform = {
            position = "0.1, 0.8, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "MainMenuReturn",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            width = "0.3",
            height = "0.2",
            onClick = "popScenePause"
        }
    },
    focusPause = {
        Transform = {
            position = "0, 0, 200",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Focus = {
            overlayName = "FocusElementPause",
            imageName = "SelectorFoco"
        }
    }
}

function popScenePause()
    local sceneMan = SceneManager.getSceneMan();
    sceneMan:popScene("testMenu");
end

function setMasterVolume(volume)
    local audioMan = AudioManager.getAudioMan();
    audioMan:setMasterVolume(volume);
end

function setMusicVolume(volume)
    local audioMan = AudioManager.getAudioMan();
    audioMan:setMusicVolume(volume);
end

function setEffectsVolume(volume)
    local audioMan = AudioManager.getAudioMan();
    audioMan:setSFXVolume(volume);
end

pause_entities = {"masterVolumeText", "masterVolume", "musicVolumeText", "musicVolume", "effectsVolumeText", "effectsVolume", "mainMenuButton", "focusPause"}