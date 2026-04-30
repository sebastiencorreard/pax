export default defineNuxtConfig({
  ssr: false,
  devtools: { enabled: true },
  modules: [
    '@nuxtjs/tailwindcss',
    '@pinia/nuxt',
    '@vueuse/nuxt',
    '@nuxtjs/i18n',
  ],
  i18n: {
    locales: [
      { code: 'fr', name: 'Français', file: 'fr.json' },
      { code: 'en', name: 'English',  file: 'en.json' },
    ],
    defaultLocale: 'fr',
    lazy: false,
    langDir: '../locales/',
    strategy: 'no_prefix',
  },
  runtimeConfig: {
    public: {
      apiBase: process.env.NUXT_PUBLIC_API_BASE || 'http://localhost:8001',
    },
  },
  app: {
    head: {
      title: 'PAX — Progrès en Automatismes par les eXercices',
      meta: [
        { charset: 'utf-8' },
        { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      ],
      link: [],
    },
  },
  css: ['~/assets/css/main.css', 'katex/dist/katex.min.css'],
})
