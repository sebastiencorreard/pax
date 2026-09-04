<template>
  <div class="min-h-screen flex flex-col" style="background:var(--color-bg);color:var(--color-text)">
    <LayoutAppNav />
    <main class="flex-1 mx-auto w-full px-4 py-8 max-w-7xl">
      <slot />
    </main>
    <footer
class="border-t py-4 text-center text-xs space-y-1"
            style="border-color:var(--color-border);color:var(--color-text-muted)">
      <div>PAX · Progrès en Automatismes par les eXercices</div>
      <div class="space-x-3">
        <NuxtLink to="/legal/cgu" class="hover:underline">{{ $t('legal.cgu.title') }}</NuxtLink>
        <NuxtLink to="/legal/licences" class="hover:underline">{{ $t('legal.licences.title') }}</NuxtLink>
        <NuxtLink to="/legal/manifeste" class="hover:underline">{{ $t('legal.manifeste.title') }}</NuxtLink>
      </div>
    </footer>
  </div>
</template>
