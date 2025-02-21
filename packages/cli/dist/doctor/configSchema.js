"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Joi = require("joi");
const schema = Joi.object().keys({
    'projectName': Joi.string().required(),
    'date': Joi.date(),
    'designWidth': Joi.number().integer(),
    'deviceRatio': Joi.object().pattern(Joi.number(), Joi.number()),
    'sourceRoot': Joi.string().required(),
    'outputRoot': Joi.string().required(),
    // NOTE: 考虑是否增加第三方模块的配置检查
    'plugins': Joi.object().pattern(Joi.string(), Joi.object()),
    'env': Joi.object().pattern(Joi.string(), Joi.string()),
    'defineConstants': Joi.object().pattern(Joi.string(), Joi.string()),
    'copy': Joi.object().keys({
        'patterns': Joi.array().items(Joi.object().keys({
            'from': Joi.string().required(),
            'to': Joi.string().required(),
            'ignore': Joi.string()
        })),
        'options': Joi.object().keys({
            'ignore': Joi.array().items(Joi.string())
        })
    }),
    'weapp': Joi.object().keys({
        'compile': Joi.object().keys({
            'exclude': Joi.array().items(Joi.string())
        }),
        'module': Joi.object(),
        'jsxAttributeNameReplace': Joi.object().pattern(Joi.string(), Joi.string())
    }),
    'alias': Joi.object().pattern(Joi.string(), Joi.string()),
    'h5': Joi.object().keys({
        'devServer': Joi.object(),
        'publicPath': Joi.string(),
        'staticDirectory': Joi.string(),
        'chunkDirectory': Joi.string(),
        'webpackChain': Joi.func(),
        'webpack': Joi.forbidden(),
        // https://webpack.js.org/configuration/resolve/#resolve-alias
        'alias': Joi.object().pattern(Joi.string(), Joi.string().strict()),
        // https://webpack.js.org/configuration/entry-context/#entry
        'entry': Joi.alternatives(Joi.string(), Joi.array().items(Joi.alternatives(Joi.string(), Joi.object().pattern(Joi.string(), Joi.alternatives(Joi.string(), Joi.array().items(Joi.string()))))), Joi.func()),
        'enableSourceMap': Joi.bool(),
        'enableExtract': Joi.bool(),
        'cssLoaderOption': Joi.object(),
        'styleLoaderOption': Joi.object(),
        'sassLoaderOption': Joi.object(),
        'lessLoaderOption': Joi.object(),
        'stylusLoaderOption': Joi.object(),
        'mediaUrlLoaderOption': Joi.object(),
        'fontUrlLoaderOption': Joi.object(),
        'imageUrlLoaderOption': Joi.object(),
        'miniCssExtractPluginOption': Joi.object(),
        'module': Joi.object().keys({
            'postcss': Joi.object().pattern(Joi.string(), Joi.object().keys({
                'enable': Joi.bool(),
                'config': Joi.object() // 第三方配置
            }))
        })
    })
});
exports.default = schema;
