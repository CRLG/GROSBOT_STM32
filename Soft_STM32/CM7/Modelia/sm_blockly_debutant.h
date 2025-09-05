/**
 * Generated 17_05_2023 at 17_34
 */

#ifndef SM_BLOCKLY_DEBUTANT_H_
#define SM_BLOCKLY_DEBUTANT_H_

#include "sm_statemachinebase.h"

class SM_BlocklyDebutant : public SM_StateMachineBase
{
public:
    SM_BlocklyDebutant()
    {
        m_main_mission_type = false;
        m_max_score = 0;
    }
    virtual void step() = 0;

    //const char* stateToName(unsigned short state);

    typedef enum {
        STATE_1 = SM_StateMachineBase::SM_FIRST_STATE,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7,
        STATE_8,
        STATE_9,
        STATE_10,
        STATE_11,
        STATE_12,
        STATE_13,
        STATE_14,
        STATE_15,
        STATE_16,
        STATE_17,
        STATE_18,
        STATE_19,
        STATE_20,
        STATE_21,
        STATE_22,
        STATE_23,
        STATE_24,
        STATE_25,
        STATE_26,
        STATE_27,
        STATE_28,
        STATE_29,
        STATE_30,
        STATE_31,
        STATE_32,
        STATE_33,
        STATE_34,
        STATE_35,
        STATE_36,
        STATE_37,
        STATE_38,
        STATE_39,
        STATE_40,
        STATE_41,
        STATE_42,
        STATE_43,
        STATE_44,
        STATE_45,
        STATE_46,
        STATE_47,
        STATE_48,
        STATE_49,
        STATE_50,
        STATE_51,
        STATE_52,
        STATE_53,
        STATE_54,
        STATE_55,
        STATE_56,
        STATE_57,
        STATE_58,
        STATE_59,
        STATE_60,
        STATE_61,
        STATE_62,
        STATE_63,
        STATE_64,
        STATE_65,
        STATE_66,
        STATE_67,
        STATE_68,
        STATE_69,
        STATE_70,
        STATE_71,
        STATE_72,
        STATE_73,
        STATE_74,
        STATE_75,
        STATE_76,
        STATE_77,
        STATE_78,
        STATE_79,
        STATE_80,
        STATE_81,
        STATE_82,
        STATE_83,
        STATE_84,
        STATE_85,
        STATE_86,
        STATE_87,
        STATE_88,
        STATE_89,
        STATE_90,
        STATE_91,
        STATE_92,
        STATE_93,
        STATE_94,
        STATE_95,
        STATE_96,
        STATE_97,
        STATE_98,
        STATE_99,
        STATE_100,
        STATE_101,
        STATE_102,
        STATE_103,
        STATE_104,
        STATE_105,
        STATE_106,
        STATE_107,
        STATE_108,
        STATE_109,
        STATE_110,
        STATE_111,
        STATE_112,
        STATE_113,
        STATE_114,
        STATE_115,
        STATE_116,
        STATE_117,
        STATE_118,
        STATE_119,
        STATE_120,
        STATE_121,
        STATE_122,
        STATE_123,
        STATE_124,
        STATE_125,
        STATE_126,
        STATE_127,
        STATE_128,
        STATE_129,
        STATE_130,
        STATE_131,
        STATE_132,
        STATE_133,
        STATE_134,
        STATE_135,
        STATE_136,
        STATE_137,
        STATE_138,
        STATE_139,
        STATE_140,
        STATE_141,
        STATE_142,
        STATE_143,
        STATE_144,
        STATE_145,
        STATE_146,
        STATE_147,
        STATE_148,
        STATE_149,
        STATE_150,
        STATE_151,
        STATE_152,
        STATE_153,
        STATE_154,
        STATE_155,
        STATE_156,
        STATE_157,
        STATE_158,
        STATE_159,
        STATE_160,
        STATE_161,
        STATE_162,
        STATE_163,
        STATE_164,
        STATE_165,
        STATE_166,
        STATE_167,
        STATE_168,
        STATE_169,
        STATE_170,
        STATE_171,
        STATE_172,
        STATE_173,
        STATE_174,
        STATE_175,
        STATE_176,
        STATE_177,
        STATE_178,
        STATE_179,
        STATE_180,
        STATE_181,
        STATE_182,
        STATE_183,
        STATE_184,
        STATE_185,
        STATE_186,
        STATE_187,
        STATE_188,
        STATE_189,
        STATE_190,
        STATE_191,
        STATE_192,
        STATE_193,
        STATE_194,
        STATE_195,
        STATE_196,
        STATE_197,
        STATE_198,
        STATE_199,
        STATE_200,
        STATE_201,
        STATE_202,
        STATE_203,
        STATE_204,
        STATE_205,
        STATE_206,
        STATE_207,
        STATE_208,
        STATE_209,
        STATE_210,
        STATE_211,
        STATE_212,
        STATE_213,
        STATE_214,
        STATE_215,
        STATE_216,
        STATE_217,
        STATE_218,
        STATE_219,
        STATE_220,
        STATE_221,
        STATE_222,
        STATE_223,
        STATE_224,
        STATE_225,
        STATE_226,
        STATE_227,
        STATE_228,
        STATE_229,
        STATE_230,
        STATE_231,
        STATE_232,
        STATE_233,
        STATE_234,
        STATE_235,
        STATE_236,
        STATE_237,
        STATE_238,
        STATE_239,
        STATE_240,
        STATE_241,
        STATE_242,
        STATE_243,
        STATE_244,
        STATE_245,
        STATE_246,
        STATE_247,
        STATE_248,
        STATE_249,
        STATE_250,
        STATE_251,
        STATE_252,
        STATE_253,
        STATE_254,
        STATE_255,
        STATE_256,
        STATE_257,
        STATE_258,
        STATE_259,
        STATE_260,
        STATE_261,
        STATE_262,
        STATE_263,
        STATE_264,
        STATE_265,
        STATE_266,
        STATE_267,
        STATE_268,
        STATE_269,
        STATE_270,
        STATE_271,
        STATE_272,
        STATE_273,
        STATE_274,
        STATE_275,
        STATE_276,
        STATE_277,
        STATE_278,
        STATE_279,
        STATE_280,
        STATE_281,
        STATE_282,
        STATE_283,
        STATE_284,
        STATE_285,
        STATE_286,
        STATE_287,
        STATE_288,
        STATE_289,
        STATE_290,
        STATE_291,
        STATE_292,
        STATE_293,
        STATE_294,
        STATE_295,
        STATE_296,
        STATE_297,
        STATE_298,
        STATE_299,
        STATE_300,
        STATE_301,
        STATE_302,
        STATE_303,
        STATE_304,
        STATE_305,
        STATE_306,
        STATE_307,
        STATE_308,
        STATE_309,
        STATE_310,
        STATE_311,
        STATE_312,
        STATE_313,
        STATE_314,
        STATE_315,
        STATE_316,
        STATE_317,
        STATE_318,
        STATE_319,
        STATE_320,
        STATE_321,
        STATE_322,
        STATE_323,
        STATE_324,
        STATE_325,
        STATE_326,
        STATE_327,
        STATE_328,
        STATE_329,
        STATE_330,
        STATE_331,
        STATE_332,
        STATE_333,
        STATE_334,
        STATE_335,
        STATE_336,
        STATE_337,
        STATE_338,
        STATE_339,
        STATE_340,
        STATE_341,
        STATE_342,
        STATE_343,
        STATE_344,
        STATE_345,
        STATE_346,
        STATE_347,
        STATE_348,
        STATE_349,
        STATE_350,
        STATE_351,
        STATE_352,
        STATE_353,
        STATE_354,
        FIN_MISSION
    }tState;
};


class SM_Tache1 : public SM_BlocklyDebutant
{
public :
    SM_Tache1() {
        m_main_mission_type = true;
    }
    void step();
    const char* getName() { return "SM_Tache1"; }
};

class SM_Tache2 : public SM_BlocklyDebutant
{
public :
    SM_Tache2() { }
    void step();
    const char* getName() { return "SM_Tache2"; }
};

class SM_Tache3 : public SM_BlocklyDebutant
{
public :
    SM_Tache3() { }
    void step();
    const char* getName() { return "SM_Tache3"; }
};

class SM_Tache4 : public SM_BlocklyDebutant
{
public :
    SM_Tache4() { }
    void step();
    const char* getName() { return "SM_Tache4"; }
};

class SM_Tache5 : public SM_BlocklyDebutant
{
public :
    SM_Tache5() { }
    void step();
    const char* getName() { return "SM_Tache5"; }
};

class SM_Tache6 : public SM_BlocklyDebutant
{
public :
    SM_Tache6() { }
    void step();
    const char* getName() { return "SM_Tache6"; }
};

class SM_Tache7 : public SM_BlocklyDebutant
{
public :
    SM_Tache7() { }
    void step();
    const char* getName() { return "SM_Tache7"; }
};

class SM_Tache8 : public SM_BlocklyDebutant
{
public :
    SM_Tache8() { }
    void step();
    const char* getName() { return "SM_Tache8"; }
};

class SM_Tache9 : public SM_BlocklyDebutant
{
public :
    SM_Tache9() { }
    void step();
    const char* getName() { return "SM_Tache9"; }
};

class SM_Tache10 : public SM_BlocklyDebutant
{
public :
    SM_Tache10() { }
    void step();
    const char* getName() { return "SM_Tache10"; }
};


#endif // SM_BLOCKLY_DEBUTANT_H_
