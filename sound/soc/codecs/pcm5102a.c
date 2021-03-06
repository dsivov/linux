/*
 * Driver for the PCM5102A codec
 *
 * Author:	Florian Meier <florian.meier@koalo.de>
 *		Copyright 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <sound/soc.h>

static int ddpl_mute(struct snd_soc_dai *dai, int mute);
static struct gpio_desc *snd_rpi_ddplayer_mute;

static const struct snd_soc_dai_ops ddpl_ops = {
        .digital_mute = ddpl_mute,
};

static struct snd_soc_dai_driver pcm5102a_dai = {
	.name = "pcm5102a-hifi",
	.playback = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE
	},
        .ops = &ddpl_ops,
};


static struct snd_soc_codec_driver soc_codec_dev_pcm5102a;

static int pcm5102a_probe(struct platform_device *pdev)
{
  printk("DDPLAYER CODEC PROBE\n");
  snd_rpi_ddplayer_mute = devm_gpiod_get(&pdev->dev, "mute",
			GPIOD_OUT_LOW);
	if (IS_ERR(snd_rpi_ddplayer_mute)) {
		printk("Cant't get mute from gpio\n");
	}
	return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_pcm5102a,
			&pcm5102a_dai, 1);
}

static int pcm5102a_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static int ddpl_mute(struct snd_soc_dai *dai, int mute)
{
        //struct snd_soc_codec *codec = dai->codec;
        if (mute)
        {
                printk("DDPLAYER MUTE\n");
                gpiod_set_value_cansleep(snd_rpi_ddplayer_mute, 1);
        }
        else
        {
                printk("DDPLAYER UNMUTE\n");
                gpiod_set_value_cansleep(snd_rpi_ddplayer_mute, 0);
        }
        return 0;
}


static const struct of_device_id pcm5102a_of_match[] = {
	{ .compatible = "ti,pcm5102a", },
	{ }
};
MODULE_DEVICE_TABLE(of, pcm5102a_of_match);

static struct platform_driver pcm5102a_codec_driver = {
	.probe		= pcm5102a_probe,
	.remove		= pcm5102a_remove,
	.driver		= {
		.name	= "pcm5102a-codec",
		.of_match_table = pcm5102a_of_match,
	},
};

module_platform_driver(pcm5102a_codec_driver);

MODULE_DESCRIPTION("ASoC PCM5102A codec driver");
MODULE_AUTHOR("Florian Meier <florian.meier@koalo.de>");
MODULE_LICENSE("GPL v2");
